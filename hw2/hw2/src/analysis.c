#include <stdio.h>
#include <stdlib.h>

#include "dyn_array.h"
#include "processing_scheduling.h"

#define FCFS "FCFS"
#define P "P"
#define RR "RR"
#define SJF "SJF"

// Add and comment your analysis code in this function.
// THIS IS NOT FINISHED.
int main(int argc, char **argv) 
{
    if (argc < 3) 
    {
        printf("%s <pcb file> <schedule algorithm> [quantum]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // seperates and stores the command line arguements
    const char *pcb_file = argv[1];
    const char *algorithm = argv[2];
    size_t quantum = atoi(argv[3]);

    // loads the process controll blocks from the file stored in pcb_file
    dyn_array_t *pcb_array = load_process_control_blocks(pcb_file);

    // makes sure it was loaded correctly
    if(!pcb_array)
    {
        printf("pcb array error");
        return EXIT_FAILURE;
    }

    // does the first come first server
    ScheduleResult_t result;
    bool success =  false; // default value might need to change


    // checks to see which algorithm is selected and then runs it
    if(strcmp(algorithm, "first_come_first_serve") == 0)
    {
        success = first_come_first_serve(pcb_array, &result);
    }
    else if(strcmp(algorithm, "shortest_remaining_time_first") == 0)
    {
        success = shortest_remaining_time_first(pcb_array, &result);
    }
    else if (strcmp(algorithm, "priority")){
        success = priority(pcb_array, &result);
    }
    else if (strcmp(algorithm, "round_robin")){
        success = round_robin(pcb_array, &result, quantum);
    }
    else if (strcmp(algorithm, "shortest_job_first"))
    {
        success = shortest_job_first(pcb_array, &result);
    }

    // makes sure it was a success
    if(!success)
    {
        printf("Error in the scheduling algorithm \n");
        return EXIT_FAILURE;
    }

    // cleans up the pcb_array allocation
    dyn_array_destroy(pcb_array);

    // prints the results
    printf("Average Waiting Time: %.2f\n", result.average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", result.average_turnaround_time);
    printf("Total Clock Time: %lu\n", result.total_run_time);

    return EXIT_SUCCESS;
}
