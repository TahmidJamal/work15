#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    printf("This is a message from the parent\n");
    for (int i = 0; i < 2; i++) {
        printf("Starting child process #%d\n", i+1);
        int pID = fork();
        if (!pID) { // it's the child 
            int fd = open("/dev/random", O_RDONLY);
            int * rando = malloc(sizeof(int));
            read(fd, rando, sizeof(int));
            *rando = abs(((*rando)) % 16) + 5;
            printf("Child [pid: %d] is sleeping for %d seconds.\n", getpid(), *rando);
            sleep(*rando);
            printf("Child [pid: %d] is no longer sleeping.\n", getpid());
            exit(*rando); //process parent is sent a SIGCHLD signal
        }
    }
    int status = -1;
    int pID = wait(&status);
    printf("It's the parent here.\n");
    printf("Child [pid: %d] only slept for %d seconds.\n", pID, WEXITSTATUS(status));
    printf("The parent is done now.\n");
    return 0;
}