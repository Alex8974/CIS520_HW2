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

   
// Helper function for shortest_job_first that compares the burst times of teo differnt processes
int cmp_remaining_burst_time(const void *a, const void *b) {
    const ProcessControlBlock_t *process_a = a;
    const ProcessControlBlock_t *process_b = b;
    return process_a->remaining_burst_time - process_b->remaining_burst_time;
}


bool shortest_job_first(dyn_array_t *ready_queue, ScheduleResult_t *result)
{

    //Checks for bad parameters
    if (!ready_queue || !result)
    {

        return false;

    }


    dyn_array_sort(ready_queue, cmp_remaining_burst_time);

    // Initalizing statistiacl values
    double total_turnaround_time = 0;
    double total_waiting_time = 0;
    uint32_t total_run_time = 0;

    // Variables for keeping track of the current and previous completion times
    uint32_t curr_time = 0;
    uint32_t previous_completion_time = 0;

    // Iterate over the processes within the ready_queue
    for (size_t i = 0; i < dyn_array_size(ready_queue); ++i) {
        ProcessControlBlock_t *process = dyn_array_at(ready_queue, i);

        // Updates current time based on the arrival time and remaining burst time of the proces
        curr_time += process->remaining_burst_time;

        // Calculate the turnaround time and waiting time for the current process
        uint32_t turnaround_time = curr_time - process->arrival;
        uint32_t waiting_time = previous_completion_time - process->arrival;

        // Update statistic values
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
        total_run_time = curr_time;

        // Updates the previous_completion_time variable for the next loop
        previous_completion_time = curr_time;
    }

    // Calculate average values for the statistics
    result->average_turnaround_time = total_turnaround_time / dyn_array_size(ready_queue);
    result->average_waiting_time = total_waiting_time / dyn_array_size(ready_queue);
    result->total_run_time = total_run_time;

    return true;

}

 


bool priority(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    // checks to see if the input is valid
    if (ready_queue == NULL || result == NULL) return false;

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

        // removes the process
        dyn_array_erase(ready_queue, hp_index);


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
    //checking to make sure that passed in values are valid
    if(ready_queue == NULL || result == NULL) return false;
    //creating variables for stat tracking
    uint32_t total_waiting_time = 0;
    uint32_t total_turnaround_time = 0;
    //looping through the queue
    for(size_t i = 0; i < dyn_array_size(ready_queue); i++){
        //getting the process
        ProcessControlBlock_t *process = dyn_array_at(ready_queue, i);
        //if the process still has time remaining
        if(process->remaining_burst_time > quantum){
            //updating remaining time for the process
            process->remaining_burst_time -= quantum;
            //updating the total run time stat and waiting time
            result->total_run_time += quantum;
            total_waiting_time += i * quantum;
            //moving the process to the back of the queue
            dyn_array_erase(ready_queue, i);
            dyn_array_push_back(ready_queue, process);
        }
        //the process has been complete
        else{
            //updating stats
            result->total_run_time += process->remaining_burst_time;
            total_waiting_time += i * process->remaining_burst_time;
            total_turnaround_time += result->total_run_time;
            //process has been complete and removing it from queue
            process->remaining_burst_time = 0;
            dyn_array_erase(ready_queue,i);
            i--;
        }
    }
    //calculating average values
    result->average_turnaround_time = (float)total_waiting_time / dyn_array_size(ready_queue);
    result->average_waiting_time = (float)total_turnaround_time / dyn_array_size(ready_queue);

    return true;
}



// Reads the PCB burst time values from the binary file into ProcessControlBlock_t remaining_burst_time field
// for N number of PCB burst time stored in the file.
// \param input_file the file containing the PCB burst times
// \return a populated dyn_array of ProcessControlBlocks if function ran successful else NULL for an error
dyn_array_t *load_process_control_blocks(const char *input_file) 
{
    // i had to do some weird thing to get in the correct directory of the pcb.bin file not sure if this will need to be changed for others
    chdir("..");
    chdir("hw2");
    chdir("hw2");

    // opens the file in read mode
    FILE *file = fopen(input_file, "rb");

    // checks if the file opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // creates a dynamic array to store ProcessControlBlock_t objects
    dyn_array_t *pcb_array = dyn_array_create(10, sizeof(ProcessControlBlock_t), NULL);

    // checks if dynamic array creation was successful
    if (pcb_array == NULL) {
        fclose(file); // Close the file
        return NULL;
    }

    // reads burst times from the file and populate the dynamic array
    int burst_time;
    int priority;
    int arrival;
    int number_of_blocks;

    fread(&number_of_blocks, sizeof(int), 1, file);

    int loopcounter = 0;
    while(loopcounter < number_of_blocks)
    {
        // creates a new ProcessControlBlock_t object
        ProcessControlBlock_t pcb;
        fread(&burst_time, sizeof(int),1,file);
        pcb.remaining_burst_time = burst_time;
        fread(&priority, sizeof(int), 1, file);
        pcb.priority = priority;
        fread(&arrival, sizeof(int), 1, file);
        pcb.arrival = arrival;
        pcb.started = false;

        // pushes the ProcessControlBlock_t object into the dynamic array
        if (!dyn_array_push_back(pcb_array, &pcb)) {
            fclose(file); // closes the file
            dyn_array_destroy(pcb_array); // destroies the dynamic array
            return NULL;
        }

        loopcounter++;
    }

    // closes the file
    fclose(file);

    return pcb_array;
/*
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
*/
    return false;

}

bool shortest_remaining_time_first(dyn_array_t *ready_queue, ScheduleResult_t *result) 
{
    // checks to see if the input is valid
    if (ready_queue == NULL || result == NULL) return false;

    // initializes variables to track time
    uint32_t total_waiting_time = 0;
    uint32_t total_turnaround_time = 0;
    unsigned long total_run_time = 0;

    // loops until all processes are executed
    uint32_t loopcounter = 0;
    while (dyn_array_size(ready_queue) > 0) {

        // finds the process with the shortest remaining time
        size_t shortest_index = 0;
        uint32_t shortest_time = UINT32_MAX;
        for (size_t i = 0; i < dyn_array_size(ready_queue); ++i) {
            ProcessControlBlock_t *process = dyn_array_at(ready_queue, i);
            if (process->remaining_burst_time < shortest_time && process->arrival <= loopcounter) {
                shortest_time = process->remaining_burst_time;
                shortest_index = i;
            }
        }

        // gets the process with the shortest remaining time from the ready queue
        ProcessControlBlock_t *process = dyn_array_at(ready_queue, shortest_index);

        // calculates waiting time for the process
        uint32_t wait_time = 0;
        if (!process->started) {
            wait_time = total_run_time - process->arrival;
        }

        // calculates turnaround time for the process
        uint32_t turnaround_time = wait_time + process->remaining_burst_time;

        // updates total statistics
        total_waiting_time += wait_time;
        total_turnaround_time += turnaround_time;
        total_run_time += process->remaining_burst_time;

        // removes the process from the ready queue
        dyn_array_erase(ready_queue, shortest_index);

        // update queue size
        size_t queue_size = dyn_array_size(ready_queue);

        // sets the process as started
        process->started = true;

        // updates remaining burst time for all processes
        for (size_t i = 0; i < queue_size; ++i) {
            ProcessControlBlock_t *p = dyn_array_at(ready_queue, i);
            if (!p->started && p->arrival <= total_run_time) {
                if (p->remaining_burst_time > shortest_time) {
                    p->remaining_burst_time -= shortest_time;
                } else {
                    p->remaining_burst_time = 0;
                }
            }
        }
        loopcounter++;
    }

    // calculates average time
    result->average_waiting_time = (float)total_waiting_time / dyn_array_size(ready_queue);
    result->average_turnaround_time = (float)total_turnaround_time / dyn_array_size(ready_queue);
    result->total_run_time = total_run_time;

    return true;
}
