#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int);

int main() {

	pid_t pid;
	
	struct sigaction act;	

	if((pid = fork()) > 0) {
		sigfillset(&(act.sa_mask));
        	act.sa_handler = handler;

        	sigaction(SIGINT, &act, NULL);
		pause();
	}
	else if(pid == 0) {
		sleep(1);
		printf("[child] killed\n");
		kill(getppid(), SIGINT);
	}
	else
		printf("fail to fork\n");
}

void handler(int signum) {
	printf("[parents] exit by checking child\n");  
} 
