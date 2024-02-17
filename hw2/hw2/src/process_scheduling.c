#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dyn_array.h"
#include "processing_scheduling.h"


// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

// private function
void virtual_cpu(ProcessControlBlock_t *process_control_block) 
{
    // decrement the burst time of the pcb
    --process_control_block->remaining_burst_time;
}

bool first_come_first_serve(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    //checking to make sure that the passed in values are valid
    if(ready_queue == NULL || result == NULL) return false;
    //creating variables to monitor the times
    uint32_t total_waiting_time = 0;
    uint32_t total_turnaround_time = 0;
    unsigned long total_run_time = 0;
    //looping through the queue
    for(size_t i = 0; i < dyn_array_size(ready_queue); ++i){
        //getting the process from the dyn_array
        ProcessControlBlock_t *process = dyn_array_at(ready_queue, i);
        //getting wait time and trunaround time for the process
        uint32_t wait_time = total_run_time - process->arrival;
        uint32_t turnaround_time = total_run_time - process->arrival + process->remaining_burst_time;
        //updating the time totals
        total_waiting_time += wait_time;
        total_turnaround_time += turnaround_time;
        total_run_time += process->remaining_burst_time;
        //setting the process as started
        process->started = true;
    }
    //calculating the average times
    result->average_turnaround_time = (float)total_turnaround_time / dyn_array_size(ready_queue);
    result->average_waiting_time = (float)total_waiting_time / dyn_array_size(ready_queue);
    result->total_run_time = total_run_time;

    return true;
}

bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;   
}

bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;   
}

bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    UNUSED(quantum);
    return false;
}

dyn_array_t *load_process_control_blocks(const char *input_file) 
{
    UNUSED(input_file);
    return NULL;
}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;
}
