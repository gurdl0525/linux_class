#include <stdio.h>
#include <stdlib.h>

FILE *fp;

void close() {
	fclose(fp);
}

int main()
{	
	char[1024] buffer;
	fp = fopen("testFile", "w");
	read(fp, buffer, 1024);
        printf("%s\n", buffer);
        atexit(close);
	exit(1);
}
