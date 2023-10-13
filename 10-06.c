#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	
	for(int i = 1; i < argc; i++){
		pid = fork();
		
		if(pid == 0) {
			execlp("wc", "wc", argv[i], (char*)0);
			exit(1);
		}
	}
}
