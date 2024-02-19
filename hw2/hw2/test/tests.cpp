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

TEST(first_come_first_serve, Ready_Que_Null)
{
    // creates a null dyn_array_t
    dyn_array_t* null_ready_queue = nullptr;

    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function to be tested with null ready_queue
    bool successNull = first_come_first_serve(null_ready_queue, &result);

    // Assert that the function returns false when ready_queue is null
    EXPECT_FALSE(successNull);
}

TEST(first_come_first_serve, Valid_Input) {
    // Create a dyn_array_t to represent the ready queue
    dyn_array_t *ready_queue;

    // Create some sample ProcessControlBlock_t objects and push them into the ready queue
    ProcessControlBlock_t process1, process2, process3;
    // Initialize process1, process2, process3 with some data
    dyn_array_push_back(ready_queue, &process1);
    dyn_array_push_back(ready_queue, &process2);
    dyn_array_push_back(ready_queue, &process3);

    // Create a ScheduleResult_t object
    ScheduleResult_t result;

    // Call the function with the ready queue
    bool success = first_come_first_serve(ready_queue, &result);

    // Assert that the function returns true
    EXPECT_TRUE(success);
}

TEST(load_process_control_blocks, BadFileName1)
{
    const char *src_file = " ";
    EXPECT_EQ(NULL, load_process_control_blocks(src_file));

}

TEST(load_process_control_blocks, BadFileName2)
{
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

