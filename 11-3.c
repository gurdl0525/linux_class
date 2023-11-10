#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

	putenv("MYDATA=5");
	printf("%s\n", getenv("MYDATA"));

	execl("ex1103-2", "ex1103-2", NULL);		
}
