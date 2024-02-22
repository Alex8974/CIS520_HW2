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
shortest_remaining_time_first tests
*/
TEST(shortest_remaining_time_first, Valid_Input) {
    // creates a dyn_array_t to represent the ready queue
    dyn_array_t *ready_queue = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // creates and initialize some sample ProcessControlBlock_t objects and push them into the ready queue
    ProcessControlBlock_t process1, process2, process3;
    process1.remaining_burst_time = 5;
    process1.priority = 1;
    process1.arrival = 1;
    process1.started = false;

    process2.remaining_burst_time = 1;
    process2.priority = 2;
    process2.arrival = 2;
    process2.started = false;

    process3.remaining_burst_time = 7;
    process3.priority = 2;
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

