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
    // checks to see if the input is valid
    if (ready_queue == NULL || result == NULL)
        return false;

    // initilizes variables to watch the time
    uint32_t total_waiting_time = 0;
    uint32_t total_turnaround_time = 0;
    unsigned long total_run_time = 0;

    // loops through the queue to find the process with the highest priority
    while (dyn_array_size(ready_queue) > 0) {
        // finds the process with the highest priority
        size_t hp_index = 0; // highest priority inde
        uint32_t highest_priority = UINT32_MAX; // sets it to maximum value initially
        for (size_t i = 0; i < dyn_array_size(ready_queue); ++i) {
            ProcessControlBlock_t *process = dyn_array_at(ready_queue, i);
            if (process->priority < highest_priority) {
                highest_priority = process->priority;
                hp_index = i;
            }
        }

        // gets the process with the highest priority from the ready queue
        ProcessControlBlock_t *process = dyn_array_at(ready_queue, hp_index);

        // calculates waiting time for the process
        uint32_t wait_time = total_run_time - process->arrival;

        // calculates turnaround time for the process
        uint32_t turnaround_time = wait_time + process->remaining_burst_time;

        // updates total statistics
        total_waiting_time += wait_time;
        total_turnaround_time += turnaround_time;
        total_run_time += process->remaining_burst_time;

        // do i need to remove the process?

        // sets the process as started
        process->started = true;
    }

    // calculates average times
    result->average_waiting_time = (float)total_waiting_time / dyn_array_size(ready_queue);
    result->average_turnaround_time = (float)total_turnaround_time / dyn_array_size(ready_queue);
    result->total_run_time = total_run_time;

    return true;  
}

bool round_robin(dyn_array_t *ready_queue, ScheduleResult_t *result, size_t quantum) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    UNUSED(quantum);
    return false;
}



// Reads the PCB burst time values from the binary file into ProcessControlBlock_t remaining_burst_time field
// for N number of PCB burst time stored in the file.
// \param input_file the file containing the PCB burst times
// \return a populated dyn_array of ProcessControlBlocks if function ran successful else NULL for an error
dyn_array_t *load_process_control_blocks(const char *input_file) 
{
    // Open file in read mode
    FILE *file = fopen(input_file, "rb");

    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    dyn_array_t *pcb_array = malloc(sizeof(dyn_array_t));

    if (pcb_array == NULL)
    {
	
	// Returns null if array is empty 
        fclose(file);
        return NULL;

    }

    // Initialize dyn_array_t
    pcb_array->size = 0;
    pcb_array->capacity = 10; // Initial capacity
    pcb_array->array = malloc(pcb_array->capacity * sizeof(ProcessControlBlock_t));

    if (pcb_array->array == NULL)
    {
	// Return null if memory is not allocated and close file
        fclose(file);

	// Free memory
        free(pcb_array);
        return NULL;
    }

    // Read burst times from file
    while (fread(&pcb_array->array[pcb_array->size].remaining_burst_time, sizeof(int), 1, file) == 1) {
        pcb_array->size++;

   	if (pcb_array->array == NULL)
        {
        	//Returnns null if array and closes file
                fclose(file);

                //Free memory
                free(pcb_array);
                return NULL;

       }

        // Resize if necessary
        if (pcb_array->size >= pcb_array->capacity)
        {

            pcb_array->capacity *= 2; // Double capacity
            pcb_array->array = realloc(pcb_array->array, pcb_array->capacity * sizeof(ProcessControlBlock_t));
           
        }
    }
    
    // Close file
    fclose(file);
    return pcb_array;

    return false;

}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    UNUSED(ready_queue);
    UNUSED(result);
    return false;
}
