// closh.c - COSC 315, Winter 2020
// YOUR NAME HERE

#include <sys/types.h>
#include<sys/wait.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char *cmd, char **cmdTokens) {
	cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
	int i = 0;
	cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
	while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
		cmdTokens[i] = strtok(NULL, " ");
	}
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
	char c = getchar();
	while (getchar() != '\n')
		;
	return c;
}

// main method - program entry point
int main() {
	char cmd[81]; // array of chars (a string)
	char *cmdTokens[20]; // array of strings
	int count; // number of times to execute command
	int parallel; // whether to run in parallel or sequentially
	int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)

	while (TRUE) { // main shell input loop

		// begin parsing code - do not modify
		printf("closh> ");
		fflush(stdout);
		fgets(cmd, sizeof(cmd), stdin);
		if (cmd[0] == '\n')
			continue;
		readCmdTokens(cmd, cmdTokens);
		do {
			printf("  count> ");
			count = readChar() - '0';
		} while (count <= 0 || count > 100);

		printf("  [p]arallel or [s]equential> ");
		parallel = (readChar() == 'p') ? TRUE : FALSE;
		do {
			printf("  timeout> ");
			timeout = readChar() - '0';
		} while (timeout < 0 || timeout > 9);
		// end parsing code

		////////////////////////////////////////////////////////
		//                                                    //
		// TODO: use cmdTokens, count, parallel, and timeout  //
		// to implement the rest of closh                     //
		//                                                    //
		// /////////////////////////////////////////////////////

		// TODO the program must run 0 - 9 times --> implement using fork()
		// each new process must print its process id before executing the command

		// TODO the program must run code serially or in parallel

		// TODO an optional timeout must be implemented 0 = no timeout, 1-9 = duration of timeout
		// the timeout dictates the maximum duration of each process

		// check if program is serial or parallel
		clock_t current, endtime;
		current = clock();// gets current clock cycles
		if(timeout>0){//only initializes if timeout = 0
		endtime = (timeout * CLOCKS_PER_SEC)+current;//gets how many cpu sycles should have elapse as timeout 
		}else{
			endtime = -1;
		}
		
	
		if (parallel) {
			// execute program in parallel

			while(count-- > 0) {
				pid_t forkPid = fork();

				//checks at start if a timeout has occurred
				if(clock() >= endtime && endtime !=-1){
					printf("timeout occured\n"); fflush(stdout);
					kill(0, SIGKILL);
				}

				// check if process is parent or child (pid is zero when child)
				if(!forkPid) {
					//checks if a timeout has occurred
					if(clock() >= endtime && endtime !=-1){
					printf("timeout occured\n"); fflush(stdout);
					kill(0, SIGKILL);
				}
					// print process ID
					printf("Process ID: %d\n", getpid());
					fflush(stdout);
					// execute command
					execvp(cmdTokens[0], cmdTokens);
					// exit process to prevent duplicate child processes
					exit(0);
				}

				// check if fork command returns error (-1)
				if(forkPid < 0 ) {
					printf("uh oh\n");
					perror("fork");
			    	abort();
				}
			}

			wait(NULL);

		} else {
			//checks at start if a timeout has occurred
			if(clock() >= endtime && endtime !=-1){
					printf("timeout occured\n"); fflush(stdout);
					kill(0, SIGKILL);
				}
			// execute program in series

			for (int i = 0; i < count; ++i) {
				//checks at start of loop if a timeout has occurred
				if(clock() >= endtime && endtime !=-1){
					printf("timeout occured\n"); fflush(stdout);
					kill(0, SIGKILL);
				}
				// print process ID
				pid_t forkPid = fork();
				if(!forkPid) {
					// print process ID
					printf("Process ID: %d\n", getpid());
					// execute command
					execvp(cmdTokens[0], cmdTokens);
				} else {
					wait(NULL);
				}
			}
		}
	}
}

