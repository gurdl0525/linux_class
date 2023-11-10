#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {

	static struct sigaction act;

	void int_handle(int);

	act.sa_handler = int_handle; 
	sigfillset(&(act.sa_mask)); 
	sigaction(SIGINT, &act, NULL);

	while(1) {
		printf("i'm sleepy..\n"); 
		
		sleep(1); 
	}
}

void int_handle(int signum) {
	printf("\nSIGINT:%d\n", signum);
	printf("system off by signal\n");

	FILE* fp = fopen("test.txt","w"); 
	fputs("system off now\n", fp);
}
