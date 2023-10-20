#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	
	pid = atoi(argv[1]);

	printf("process id:%d, group id:%d, session id:%d\n", pid, getpgid(pid), getsid(pid));
	printf("process id:%d, group id:%d, session id:%d\n", getpid(), getpgrp(), getsid(0));
	
	sleep(600);
}
