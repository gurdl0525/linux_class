#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>

int main() {

	int x, y;

	int status;

	scanf("%d %d", &x, &y);

	pid_t pid;
	
	pid = fork();

	if(pid > 0) {
		double p = pow(x, y);
		wait(&status);
		printf("%d\n", (status>>8) + (int)p);
	} 
	else if(pid == 0) {
		int m = x * y;
		exit(m);
	}

}
