#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1

int main(void) {
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd)==-1) {
        perror("pipe issue");
        exit(1);
    }
    pid1=fork();
    if (pid1<0) {
        perror("fork1 issue");
        exit(1);
    }
    if (pid1==0) {
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]);

        char* comm1 = "ls";
        char* args1[] = {"ls", "-F", NULL};

        int stat = execvp(comm1, args1);
        if (stat==-1) {
            perror("command 1 issue, status");
            exit(1);
        }
    }
    pid2=fork();
    if(pid2<0) {
        perror("second fork issue");
        exit(1);
    }
    if (pid2==0) {
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO);
        close(fd[READ_END]);

        char* comm2="nl";
        char* args2[]={"nl",NULL};

        int stat=execvp(comm2, args2);
        if (stat==-1) {
            perror("second fork issue :c status");
            exit(1);
        }
    }
    close(fd[READ_END]);
    close(fd[WRITE_END]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}