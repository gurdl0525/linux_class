#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define MAX_BLOCKS 10
#define MAX_PARAMS 3
#define LOG_FILE "./log/restart.txt"
#define BLOCKS_FILE "./blocks.txt"
#define RESTART_INTERVAL 3

typedef struct {
    char name[50];
    char reason[50];
    char parameters[MAX_PARAMS][50];
    int paramCount;
    int restartCount;
    time_t startTime;
} SoftwareBlock;

SoftwareBlock blocks[MAX_BLOCKS];

int blockCount = 0;

void writeLogT(char* str1, char *str2, char *str3, char *str4) {
    FILE* file = fopen(LOG_FILE, "a");

    if (file == NULL) {
        printf("Opening log file exception\n");
        return;
    }

    fprintf(file, "%-15s%-15s%-25s%s\n", str1, str2, str3, str4);

    fclose(file);
}

void writeLogA(char* str1, int num1, char *str2, char *str3) {
    FILE* file = fopen(LOG_FILE, "a");

    if (file == NULL) {
        printf("Opening log file exception\n");
        return;
    }

    fprintf(file, "%-15s%-15d%-25s%s\n", str1, num1, str2, str3);

    fclose(file);
}

void getBlocksFromFile() {
    FILE* file = fopen(BLOCKS_FILE, "r");
    if (file == NULL) {
        printf("Opening file exception\n");
        exit(1);
    }

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL && blockCount < MAX_BLOCKS) {
        char* token = strtok(line, ";");
        strcpy(blocks[blockCount].name, token);

        token = strtok(NULL, ";");
        int paramIndex = 0;
        while (token != NULL) {
            strcpy(blocks[blockCount].parameters[paramIndex], token);
            paramIndex++;
            token = strtok(NULL, ";");
        }
        blocks[blockCount].paramCount = paramIndex;
        blockCount++;
    }

    fclose(file);
}

void init(SoftwareBlock* block) {
    printf("init : %s\n", block->name);
    block->startTime = time(NULL);
    strcpy(block->reason, "INIT");
}

void restart(SoftwareBlock* block, const char* reason) {
    printf("restart: %s\n", block->name);
    block->restartCount++;
    block->startTime = time(NULL);
    strcpy(block->reason, reason);

    char* timeStr = ctime(&block->startTime);
    timeStr[strlen(timeStr) - 1] = '\0';

    writeLogA(block->name, block->restartCount, timeStr, block->reason);
}


void handler(int signal) {

    int pid;
    int status;

    while((pid=waitpid(-1, &status, WNOHANG)) > 0) {

        int randomIndex = rand() % blockCount;
        SoftwareBlock* blockToRestart = &blocks[randomIndex];

        char restartReason[50];

        if (WIFEXITED(status)){
            snprintf(restartReason, sizeof(restartReason), "EXIT");
        }
        else if(WIFSIGNALED(status)) {
            if (signal == SIGTERM) {
                snprintf(restartReason, sizeof(restartReason), "SIGTERM");
            } else if (signal == SIGCHLD) {
                snprintf(restartReason, sizeof(restartReason), "SIGCHLD");
            } else if (signal == SIGINT) {
                snprintf(restartReason, sizeof(restartReason), "SIGINT");
            } else {
                snprintf(restartReason, sizeof(restartReason), "Killed By %d", signal);
            }
        }

        restart(blockToRestart, restartReason);
    }
}

void spawnSoftWare() {
    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (pid == 0) {
        sleep(2);
        if (rand() % 9 > 6)
            kill(getpid(), SIGKILL);
        else
            kill(getpid(), SIGINT);
        exit(0);
    } else {
        signal(SIGCHLD, handler);
        signal(SIGTERM, handler);
        signal(SIGINT, handler);
    }
}

void printStatus() {

    writeLogT("S/W Block Name", "Restart Count", "Start Time", "Reason");

    for (int i = 0; i < blockCount; i++) {
        SoftwareBlock* block = &blocks[i];
        char* timeStr = ctime(&block->startTime);
        timeStr[strlen(timeStr) - 1] = '\0';
        writeLogA(block->name, block->restartCount, timeStr, block->reason);
    }

    printf("%-15s%-15s%-25s%s\n", "S/W Block Name", "Restart Count", "Start Time", "Reason");
    for (int i = 0; i < blockCount; i++) {
        SoftwareBlock* block = &blocks[i];
        char* timeStr = ctime(&block->startTime);
        timeStr[strlen(timeStr) - 1] = '\0';
        printf("%-15s%-15d%-25s%s\n", block->name, block->restartCount, timeStr, block->reason);
    }
}

int main() {

    srand(time(NULL));
    getBlocksFromFile();

    struct sigaction act;

    sigset_t set;

    sigfillset(&(act.sa_mask));
    act.sa_handler = handler;

    sigaction(SIGCHLD, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);

    for (int i = 0; i < blockCount; i++) {
        init(&blocks[i]);
    }

    while (1) {
        sleep(RESTART_INTERVAL);
        spawnSoftWare();
        printStatus();
    }

    return 0;
}