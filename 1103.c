#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 512

int main() {

        char msg[SIZE];
        int filedes[2];

	pid_t pid;
	
	if(pipe(filedes) == -1) {
        	printf("fail to call pipe()\n");
		exit(1);
	}
	
	if((pid = fork()) == -1) {
		printf("fail to call fork()\n");
		exit(1);
	} 
	
	else if (pid > 0) {

		pid_t pid2;

		strcpy(msg, "apple is red.\n");

		if((pid2 = fork()) > 0) {
			close(filedes[0]);
			write(filedes[1], msg, SIZE);
			printf("[parent] %s\n", msg);
		}

		else if (pid2 == 0) {
			close(filedes[1]);
			sleep(1);
                	read(filedes[0], msg, SIZE);
                	printf("[child2] %s", msg);
		}
	}

	else {
		close(filedes[1]);
		sleep(1);
		read(filedes[0], msg, SIZE);
		printf("\n[child1] %s", msg);
	}
}
