#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <pthread.h>
#include "../include/processing_scheduling.h"

// Using a C library requires extern "C" to prevent function managling
extern "C"
{
#include <dyn_array.h>
#include <processing_scheduling.h>
}

#define NUM_PCB 30
#define QUANTUM 5 // Used for Robin Round for process as the run time limit

/*
priority tests
*/
TEST(priority, Valid_Input) {
    // creates a dyn_array_t to represent the ready queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // creates some sample ProcessControlBlock_t objects and push them into the ready queue
    ProcessControlBlock_t process1, process2, process3;
    process1.remaining_burst_time = 5;
    process1.priority = 3;
    process1.arrival = 0;
    process1.started = false;

    process2.remaining_burst_time = 3;
    process2.priority = 1;
    process2.arrival = 2;
    process2.started = false;

    process3.remaining_burst_time = 7;
    process3.priority = 2;
    process3.arrival = 5;
    process3.started = false;

    dyn_array_push_back(ready_queue, &process1);
    dyn_array_push_back(ready_queue, &process2);
    dyn_array_push_back(ready_queue, &process3);

    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function with the ready queue
    bool success = priority(ready_queue, &result);

    // asserts that the function returns true
    EXPECT_TRUE(success);

    for (size_t i = 1; i < dyn_array_size(ready_queue); ++i) {
        const size_t hold = i;
        ProcessControlBlock_t *prev_process = static_cast<ProcessControlBlock_t*>(dyn_array_at(ready_queue, hold - 1));
        ProcessControlBlock_t *curr_process = static_cast<ProcessControlBlock_t*>(dyn_array_at(ready_queue, hold));
        // Expect that prev_process->priority is less than or equal to curr_process->priority
        EXPECT_LE(prev_process->priority, curr_process->priority);
    }

    // frees the memory
    dyn_array_destroy(ready_queue);
}

TEST(priority, Null_ReadyQueue) {
    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function with NULL ready queue
    bool success = priority(NULL, &result);

    // asserts that the function returns false
    EXPECT_FALSE(success);
}

TEST(priority, Null_Result) {
    // creates a dyn_array_t to represent the ready queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // calls the function with NULL result
    bool success = priority(ready_queue, NULL);

    // asserts that the function returns false
    EXPECT_FALSE(success);

    // frees the memory 
    dyn_array_destroy(ready_queue);
}



/*
shortest_remaining_time_first tests
*/
TEST(shortest_remaining_time_first, Valid_Input) {
    // creates a dyn_array_t to represent the ready queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // creates and initialize some sample ProcessControlBlock_t objects and push them into the ready queue
    ProcessControlBlock_t process1, process2, process3;
    process1.remaining_burst_time = 5;
    process1.priority = 2;
    process1.arrival = 1;
    process1.started = false;

    process2.remaining_burst_time = 1;
    process2.priority = 2;
    process2.arrival = 2;
    process2.started = false;

    process3.remaining_burst_time = 7;
    process3.priority = 1;
    process3.arrival = 6;
    process3.started = false;

    dyn_array_push_back(ready_queue, &process1);
    dyn_array_push_back(ready_queue, &process2);
    dyn_array_push_back(ready_queue, &process3);

    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function with the ready queue
    bool success = shortest_remaining_time_first(ready_queue, &result);

    // asserts that the function returns true
    EXPECT_TRUE(success);

    // expted order
    std::vector<size_t> expected_order = {1, 0, 2}; 

    // Compare the actual execution order with the expected order
    for (size_t i = 0; i < dyn_array_size(ready_queue); ++i) {
    // Get the process executed at this position from the ready queue
    ProcessControlBlock_t *executed_process = static_cast<ProcessControlBlock_t*>(dyn_array_at(ready_queue, i));
    
    // Obtain the expected index of the process executed at position i
    size_t expected_index = expected_order[i];

    // Find the index of the executed process in the original array
    size_t actual_index = 0;
    for (size_t j = 0; j < dyn_array_size(ready_queue); ++j) {
        ProcessControlBlock_t *original_process = static_cast<ProcessControlBlock_t*>(dyn_array_at(ready_queue, j));
        if (executed_process == original_process) {
            actual_index = j;
            break;
        }
    }

    // Check if the executed process matches the expected process
    EXPECT_EQ(expected_index, actual_index); // Compare the expected index with the actual index
}
    // frees the memory
    dyn_array_destroy(ready_queue);
}

TEST(shortest_remaining_time_first, Null_ReadyQueue) {
    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function with NULL ready queue
    bool success = shortest_remaining_time_first(NULL, &result);

    // asserts that the function returns false
    EXPECT_FALSE(success);
}

TEST(shortest_remaining_time_first, Null_Result) {
    // creates a dyn_array_t to represent the ready queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // calls the function with NULL result
    bool success = shortest_remaining_time_first(ready_queue, NULL);

    // asserts that the function returns false
    EXPECT_FALSE(success);

    // frees the memeory
    dyn_array_destroy(ready_queue);
}


/*
first_come_first_server tests
*/
TEST(first_come_first_serve, Ready_Queue_Null)
{
    // creates a null dyn_array_t
    dyn_array_t* null_ready_queue = nullptr;

    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function to be tested with null ready_queue
    bool successNull = first_come_first_serve(null_ready_queue, &result);

    // asserts that the function returns false when ready_queue is null
    EXPECT_FALSE(successNull);
}

TEST(first_come_first_serve, Valid_Input) {
    // creates the ready queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);


    // creates some processes for the process control block
    ProcessControlBlock_t process1, process2, process3;

    // initializes process1, process2, process3 with data
    process1.remaining_burst_time = 10;
    process1.priority = 1;
    process1.arrival = 0;
    process1.started = false;

    process2.remaining_burst_time = 8;
    process2.priority = 2;
    process2.arrival = 2;
    process2.started = false;

    process3.remaining_burst_time = 15;
    process3.priority = 3;
    process3.arrival = 5;
    process3.started = false;

    dyn_array_push_back(ready_queue, &process1);
    dyn_array_push_back(ready_queue, &process2);
    dyn_array_push_back(ready_queue, &process3);

    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function with the ready queue
    bool success = first_come_first_serve(ready_queue, &result);

    // asserts that the function returns true
    EXPECT_TRUE(success);
}

/*
load_process_control_blocks test
*/

TEST(load_process_control_blocks, BadFileName1)
{
    // checks to make sure it does not try to read in a bad filename
    const char *src_file = " ";
    EXPECT_EQ(NULL, load_process_control_blocks(src_file));

}

TEST(load_process_control_blocks, BadFileName2)
{
    // checks to make sure it does not try to read in a bad filename
    const char *src_file = "\n";
    EXPECT_EQ(NULL, load_process_control_blocks(src_file));

}



/*
round_robin test
*/
TEST(round_robin, Valid_input) 
{
  
 // Create  dyn_array_t to be in place of the ready queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // Initialize sample ProcessControlBlock_t objects and push them into ready_queue
    ProcessControlBlock_t process1, process2, process3;
    process1.remaining_burst_time = 10;
    process2.remaining_burst_time = 5;
    process3.remaining_burst_time = 8;

    dyn_array_push_back(ready_queue, &process1);
    dyn_array_push_back(ready_queue, &process2);
    dyn_array_push_back(ready_queue, &process3);

    // Create a ScheduleResult_t object
    ScheduleResult_t result = {0, 0, 0};

    // Call the function with the ready queue and quantum
    size_t quantum = 3;
    bool success = round_robin(ready_queue, &result, quantum);

    // Assert that the function returns true
    EXPECT_TRUE(success);

    std::vector<size_t> expected_order = {0, 1, 2};

    // Compare the actual execution order with the expected order
    for (size_t i = 0; i < dyn_array_size(ready_queue); ++i) {
        // Get the process executed at this position from the ready queue
        ProcessControlBlock_t *executed_process = static_cast<ProcessControlBlock_t*>(dyn_array_at(ready_queue, i));

        // Obtain expected index at position i
        size_t expected_index = expected_order[i];

        // Find the index of the executed process in the original array
        size_t actual_index = 0;
        for (size_t j = 0; j < dyn_array_size(ready_queue); ++j) {
            ProcessControlBlock_t *original_process = static_cast<ProcessControlBlock_t*>(dyn_array_at(ready_queue, j));
            if (executed_process == original_process) {
                actual_index = j;
                break;
            }
        }

        EXPECT_EQ(expected_index, actual_index); // Compare expected index with  actual index
    }

    // Frees the memory
    dyn_array_destroy(ready_queue); 

}

TEST(round_robin, different_Quantum)
{

    // Create a dyn_array_t to be in palce of  ready_queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // Initialize sample ProcessControlBlock_t objects and push them into the ready queue
    ProcessControlBlock_t process1, process2, process3;
    process1.remaining_burst_time = 10;
    process2.remaining_burst_time = 5;
    process3.remaining_burst_time = 8;

    dyn_array_push_back(ready_queue, &process1);
    dyn_array_push_back(ready_queue, &process2);
    dyn_array_push_back(ready_queue, &process3);

    
    ScheduleResult_t result = {0, 0, 0};

    // Call the function with the ready queue and different quantum values
    size_t quantum1 = 3;
    bool success1 = round_robin(ready_queue, &result, quantum1);
    EXPECT_TRUE(success1);

    // Assert the result based on quantum1
    // You can add assertions here to check if the scheduling is correct based on the quantum value

    // Reset the result for the next test
    result = {0, 0, 0};

    // Call the function with a different quantum value
    size_t quantum2 = 5;
    bool success2 = round_robin(ready_queue, &result, quantum2);
    EXPECT_TRUE(success2);


    // Free memory
    dyn_array_destroy(ready_queue);
}


/*
shortest_job_first test
*/
TEST(shortest_job_first, Valid_Input)
{
    // Create dyn_array_t to represent ready_queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // Initialize sample ProcessControlBlock_t objects and push into ready_queue
    ProcessControlBlock_t process1, process2, process3;
    process1.remaining_burst_time = 10;
    process1.arrival = 0;

    process2.remaining_burst_time = 5;
    process2.arrival = 0;

    process3.remaining_burst_time = 8;
    process3.arrival = 0;

    dyn_array_push_back(ready_queue, &process1);
    dyn_array_push_back(ready_queue, &process2);
    dyn_array_push_back(ready_queue, &process3);

    // Create ScheduleResult_t object
    ScheduleResult_t result;

    // Callfunction with ready_queue
    bool success = shortest_job_first(ready_queue, &result);

    // Assert that funtion returns true
    EXPECT_TRUE(success);

    // Get expected average turnaround time
    double expected_avg_turnaround_time = (10 + 15 + 23) / 3.0;

    // Get expected average waiting time
    double expected_avg_waiting_time = ((10 + 0) + (15 + 0) + (23 + 0)) / 3.0;

    // Assert calculated average turnaround time
    EXPECT_DOUBLE_EQ(result.average_turnaround_time, expected_avg_turnaround_time);

    // Assert calculated average waiting time
    EXPECT_DOUBLE_EQ(result.average_waiting_time, expected_avg_waiting_time);

    // Assert total run time
    EXPECT_EQ(result.total_run_time, 23u);

    // Free memory
    dyn_array_destroy(ready_queue);
}

TEST(shortest_job_first, Null_Pointer_Input)
{
    // Create null-pointer for ready_queue
    dyn_array_t *ready_queue = NULL;

    // Create ScheduleResult_t object
    ScheduleResult_t result;

    // Call function with null-pointer for ready_queue
    bool success = shortest_job_first(ready_queue, &result);

    // Assertfunction returns false for null-pointer input
    EXPECT_FALSE(success);
}



TEST(shortest_job_first, Empty_Ready_Queue)
{
    // Create empty dyn_array_t to be in palce of ready_queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // Create ScheduleResult_t object
    ScheduleResult_t result;

    // Call function with empty ready_queue
    bool success = shortest_job_first(ready_queue, &result);

    // Assert thatfunction returns true for an empty ready_queue
    EXPECT_TRUE(success);

    // Freememory
    dyn_array_destroy(ready_queue);
}
                                





/*
unsigned int score;
unsigned int total;

class GradeEnvironment : public testing::Environment
{
public:
    virtual void SetUp()
    {
        score = 0;
        total = 210;
    }

    virtual void TearDown()
    {
        ::testing::Test::RecordProperty("points_given", score);
        ::testing::Test::RecordProperty("points_total", total);
        std::cout << "SCORE: " << score << '/' << total << std::endl;
    }
};
*/

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    // ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}

