# Assignment 2

Milestone 0: CMake and Unit Testing filled out. 

Milestone 1: PCB file loading and First Come First Served. 

Milestone 2: Shortest Job First, Shortest Remaining Time First, Round Robin, and analysis of algorithms. 

Note: 
You can manually copy the time analysis from console and paste it to this readme file, but directly output from your program is strongly recommended.     
---------------------------------------------------------------------------
Add your scheduling algorithm analysis below this line in a readable format. 
---------------------------------------------------------------------------
PS C:\Users\Alexander\Desktop\CIS520_HW2\build> ./analysis pcb.bin FCFS
Average Waiting Time: 16.00
Average Turnaround Time: 28.50
Total Clock Time: 50

PS C:\Users\Alexander\Desktop\CIS520_HW2\build> ./analysis pcb.bin SJF 
Average Waiting Time: 1073741824.00
Average Turnaround Time: 23.50
Total Clock Time: 50

PS C:\Users\Alexander\Desktop\CIS520_HW2\build> ./analysis pcb.bin RR 4  
Average Waiting Time: 0.00
Average Turnaround Time: 6.00
Total Clock Time: 577

PS C:\Users\Alexander\Desktop\CIS520_HW2\build> ./analysis pcb.bin SRTF
Average Waiting Time: 3.69
Average Turnaround Time: 5.25
Total Clock Time: 25

PS C:\Users\Alexander\Desktop\CIS520_HW2\build> ./analysis pcb.bin P
Average Waiting Time: 16.00
Average Turnaround Time: 28.50
Total Clock Time: 50