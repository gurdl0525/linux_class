#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int num;
	scanf("%d", &num);
	pid_t pid = fork();

	if (pid > 0) {
		// parent
		int res = 0;
		for (int i = 1; i <= num; i++) {
			res += i;
		}
		printf("%d\n", res);
	}
	else if (pid == 0) {
		// child
                int res = 1;
		for (int i = 1; i <= num; i++) {
			res *= i;
                }
                printf("%d\n", res);
	}
	else {
		printf("Fork Failed\n");
	}
}
