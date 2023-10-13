#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>

int main() {

	int x, y;

	int status;

	scanf("%d %d", &x, &y);

	pid_t pid1, pid2;
	
	pid1 = pid2 = -1;

	pid1 = fork();

	if(pid1 > 0) pid2 = fork();

	if (pid1 > 0 && pid2 > 0) {
		double p = pow(x, y);
		
		waitpid(pid2, &status, 0);

		int n2 = (status>>8);

		waitpid(pid1, &status, 0);

		int n1 = (status>>8);

		printf("pearent : %d\n", (int)p);

		printf("(3) - (2) -(1) : %d\n", n2 - n1 -(int)p);
	}
	else if(pid1 == 0 && pid2 == -1) {
		int m = 0;
		for(int i = x; i <= y; i++) {
			m += i;
		}
		printf("child1 : %d\n", m);
		exit(m);
	}
	else if(pid1 > 0 && pid2 == 0) {
		int mu = 1;
		for (int i = x; i <= y; i++) {
			mu *= i;
		}
		printf("child2 : %d\n", mu);
		exit(mu);
	}
}
