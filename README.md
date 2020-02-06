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
