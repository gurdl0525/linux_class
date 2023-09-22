#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int i = 1;
int main() {
	pid_t pid;
	pid = fork();
	
	printf("%p\n", &i);	

	if (pid > 0) {
		// parent
		printf("%d\n", ++i);
	}
	else if (pid == 0) {
		// child
		printf("%d\n", --i);
	}
	else {
		printf("Fork Failed\n");
	}
}
