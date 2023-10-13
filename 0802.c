#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	pid_t pid;

	int status;


	pid = fork();


	if (pid > 0) {
		printf("waiting\n");

		wait(&status);

		printf("status is %d\n", status);
	}

	else if(pid == 0){
		sleep(1);
		printf("bye!\n");
		exit(1);
	}
}
