                            MULTI-LEVEL QUEUE SCHEDULING
                            ============================

1.  This folder contains CPU.cpp file , Make file and the screenshots of the results of the running program.

2.  To run the CPU.cpp , first make the executable file using the command "make CPU" , 
    and then to run the executable use the command "./CPU" and enter the input in the below format :
            i)    First line contains the integer 'n' -> Number of processes.
            ii)   Second line contains the integer 'q' -> Time Quantum or Time Slice for the Round Robin of queues.
            iii)  Next 'n' lines contains the info about the process in the format : "process-id arrival-time burst-time process-type priority".

3.  Example :- 
                5           --> 'n'= Number of processes
                3           --> 'q'= Time Quantum or Time Slice
                1 0 3 0 1   -->  P1= pid=1 , at=0 , bt=3 , type=sys , prio=1
                2 2 2 1 0   -->  P2= pid=2 , at=2 , bt=2 , type=ip , prio=0
                3 3 2 2 0   -->  P3= pid=3 , at=3 , bt=2 , type=iep , prio=0
                4 5 3 3 0   -->  P4= pid=4 , at=5 , bt=3 , type=bp , prio=0
                5 6 1 4 0   -->  P5= pid=5 , at=6 , bt=4 , type=sp , prio=0

4.  Output format is the Gant Chart with the process in the CPU in the time slot of 1 unit.
    and the Statistics such as Completion time , Turn Around time , Waiting time regarding the processes.