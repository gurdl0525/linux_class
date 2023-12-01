#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int main() {

        int p[2];
        char file1 = "a.txt";
        charfile2 = "b.txt";

        pid_t pid;

        int pSize, fd_read;

        if(pipe(p) == -1) {
                printf("fail to call pipe()\n");
                exit(1);
        }

        pSize = fpathconf(p[1], _PC_PIPE_BUF);

        if((pid = fork()) == -1) {
                printf("fail to call fork()\n");
                exit(1);
        }

        else if(pid > 0) {
                printf("[parent]\n");
                close(p[0]);

                fd_read = open(file1, O_RDONLY);

                if (strSize > pSize) {

                        while(nread = read()
                        for (int i = 0; i < strSize; i + pSize) {

                                char buf = malloc(sizeof(char) pSize);

                                for (int j = 0; j < pSize; j++)
                                        buf[j] = msg[i];

                                write(p[1], buf, pSize);

                                free(buf);
                        }
                }

                else
                        write(p[1], msg, strSize);
        }

        else {
                printf("[child]\n");

                sleep(3);
                printf("%s", p[0]);

        }
 } 
