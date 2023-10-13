#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>

int main() {

	int status;
	
	pid_t pid[3][2];

	pid_t pid1, pid2;
	
	pid1 = pid2 = -1;

	pid1 = fork();

	if(pid1 > 0) pid2 = fork();

	if (pid1 > 0 && pid2 > 0) {

		pid[0][0] = getpid();
		pid[0][1] = getppid();	
		
		waitpid(pid2, &status, 0);

		waitpid(pid1, &status, 0);

		printf("%d, %d\n%d, %d\n%d, %d\n", pid[0][0], pid[0][1], pid[1][0], pid[1][1], pid[2][0], pid[2][1]);

	}
	else if(pid1 == 0 && pid2 == -1) {
		pid[1][0] = getpid();
		pid[1][1] = getppid();
		printf("child1 : %d\n", pid[1][0]);
		exit(1);
	}
	else if(pid1 > 0 && pid2 == 0) {
		pid[2][0] = getpid();
		pid[2][1] = getppid();
		printf("child2 : %d\n", pid[2][0]);
		exit(2);
	}
}
