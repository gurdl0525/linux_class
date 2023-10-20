#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main() {
	pid_t pid;

	while (1) {
		pid = fork();
		
		if (pid > 0) {
			time_t t = time(NULL);
			struct tm *ptm = gmtime(&t);
			printf("%d %d %d %d %d %d\n", ptm->tm_year, ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
			exit(0);
		}
		else if(pid == 0) {
			sleep(10);
		}
	}
}
