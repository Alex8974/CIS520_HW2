#include <fcntl.h>
#include <stdio.h>
#include "gtest/gtest.h"
#include <pthread.h>
#include "../include/processing_scheduling.h"

// Using a C library requires extern "C" to prevent function managling
extern "C"
{
#include <dyn_array.h>
}

#define NUM_PCB 30
#define QUANTUM 5 // Used for Robin Round for process as the run time limit

TEST(first_come_first_serve, ReadyQueNotNull)
{
    // creates a null dyn_array_t
    dyn_array_t* null_ready_queue = nullptr;

    // creates a ScheduleResult_t object
    ScheduleResult_t result;

    // calls the function to be tested with null ready_queue
    bool success_null = first_come_first_serve(null_ready_queue, &result);

    // Assert that the function returns false when ready_queue is null
    EXPECT_FALSE(success_null);
}

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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GradeEnvironment);
    return RUN_ALL_TESTS();
}

