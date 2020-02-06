# OS_Project1
Repo for Project 1 of COSC 315.
## Contributions
**Group 21** <br>
**Kyle Ranslam:** Parallel and Sequential Code<br>
**David Ding:** Parallel and Sequential Code<br>
**Devon MacNeil:** Timeouts<br>

## Desgin Choices

### Parallel Code
The program first checks whether the forks are to be executed in parallel or serially. <br>
During the parallel implementation, the count is to be used together with a while loop. Each iteration of the loop decrements the count by 1 until it reaches 0.<br>
Inside each loop iteration, a fork is made. The returned pid from the fork function is then checked to see if it is zero.<br>
A pid value of 0 means that the current process is a child process, and should run the execvp command to run the shell command.<br>
A non-zero pid value means that the current process is the parent process, and should continue to fork new threads on the next iterations of the while loop.<br>
### Sequential Code
The sequential portion of the code consists of a for loop that forks a process. Within the loop, if the process is a child then it will print its PID and then execute the program. <br> 
If it is the parent process then it waits until the child process is done executing (using wait()) before forking another child process. <br>
Both the Parallel and Sequential code check if the fork is performed correctly and returns an error message if it doesn't.

### Timeout Implementation
Primary design choice was to initialize the timeout directly after the timeout number in seconds is given this is so it is initialized once per run. <br>
Next was to base the timeout period on the number of CPU’s clock cycles. This is to give more reliability between different CPU’s with the endtime being the CPU’s number of clock cycles multiplied by the number of seconds given by the user added to the number of clock cycle since the programs start. This way if the user sits on an option for a few minutes the timeout won’t immediately occur.<br>
It also checks if a timeout has been set with it initializing endtime to -1 to show that there is no timeout. 
The timeout then checks for a timeout at the start of each loop or binary check. If a timeout does occur it kills the process using kill(0, SIGKILL) as suggested in the project pdf. <br>
An if else statement was used to check if a timeout occurs as this method is universal and uses minimal clock cycles.
