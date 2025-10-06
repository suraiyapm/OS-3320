// Suraiya Poberezhsky Mark, EMPLID: 23756247

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1
// The definitions make sense for consistency, and I'm guessing are industry-standard, but they feel a bit long to me (for what they are).
// I put those here since they are in the examples in the textbook, so I imagine are a good practice.

int main(void) {
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd)==-1) { // Single direction communication for the processes.
        perror("pipe issue");
        exit(1);
    }
    pid1=fork(); // duplicates into new process. Runs same as parent, but with the pid value logic. The child gets 0, parent gets a positive int for the child's pid.
    if (pid1<0) { // child not made
        perror("fork1 issue"); // Writing it to std error: https://manpages.ubuntu.com/manpages/questing/en/man3/perror.3posix.html
        exit(1);
    }
    if (pid1==0) { // child is active
        close(fd[READ_END]); //closes file descrip., so read end here since not needed by the first child (first writes, second reads)
        dup2(fd[WRITE_END], STDOUT_FILENO); // duplicates file descriptor, uses specified one
        close(fd[WRITE_END]);

        char* comm1 = "ls";
        char* args1[] = {"ls", "-F", NULL};

        int stat = execvp(comm1, args1); // replaces current proc image with new https://man7.org/linux/man-pages/man3/exec.3.html
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

    waitpid(pid1, NULL, 0); // suspends exec of calling thread until child specified by pid arg has changed state https://manpages.ubuntu.com/manpages/questing/en/man2/waitpid.2.html
    waitpid(pid2, NULL, 0);
    return 0;
}
/*

Misc links used (pretty much entirely from links from the assignment sheet, the manpages, or echo file):

https://man7.org/linux/man-pages/man3/exec.3.html
https://manpages.ubuntu.com/manpages/questing/en/man2/waitpid.2.html
https://manpages.ubuntu.com/manpages/noble/en/man3/access.3posix.html
https://manpages.ubuntu.com/manpages/questing/en/man2/access.2freebsd.html
https://manpages.ubuntu.com/manpages/questing/en/man3/perror.3posix.html
https://cs.brown.edu/courses/csci0300/2022/notes/l19.html
https://manpages.ubuntu.com/manpages/questing/en/man7/pipe.7.html
https://www.digitalocean.com/community/tutorials/execvp-function-c-plus-plus
https://www.dropbox.com/scl/fo/3z5ot6qr99itnuupkosb3/ACKitIh13atPpHwSetWeYXQ/source%20code?e=1&preview=echo.txt&rlkey=ey74b0tvsw3gkzahense6700n&subfolder_nav_tracking=1&dl=0
(then just lecture slides and textbook itself)

*/