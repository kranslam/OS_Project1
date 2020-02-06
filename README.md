# OS_Project1
**Group 21** <br>
Repo for Project 1 of COSC 315.
## Contributions
**Kyle Ranslam:** Parallel and Sequential Code<br>
**David Ding:** Parallel and Sequential Code<br>
**Devon MacNeil:** Timeouts<br>

## Desgin Choices

### Parallel Code
The count is to be used together with a while loop, with each iteration of the loop decrementing the count by 1 until it reaches 0.<br>
Inside each loop iteration, a fork is made. The returned pid from the fork function is then chedked to see if it is zero.<br>
A zero pid value means that the current process is a child process, and should run the execvp command to run the shell command.<br>
A non-zero pid value means that the current process is the parent process, and should continue to fork new threads on the next iterations of the while loop.<br>
### Sequential Code

### Timeout Implementation
Primary design choice was to initialize the timeout directly after the timeout number in seconds is given this is so it is initialized once per run. Next was to base the timeout period on the number of CPU’s clock cycles. This is to give more reliability between different CPU’s with the endtime being the CPU’s number of clock cycles multiplied by the number of seconds given by the user added to the number of clock cycle since the programs start. This way if the user sits on an option for a few minutes the timeout won’t immediately occur. It also checks if a timeout has been set with it initializing endtime to -1 to show that there is no timeout. The timeout then checks for a timeout at the start of each loop or binary check. If a timeout does occur it kills the process using kill(0, SIGKILL) as suggested in the project pdf. An if else statement was used to check if a timeout occurs as this method is universal and uses minimal clock cycles.
