// Suraiya Poberezhsky Mark

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {

    int fd;
    mode_t ifDoesnExist, readwritemode;
    ifDoesnExist = O_CREAT;
    readwritemode = O_RDWR;
    fd = open("hello_brooklyn.txt", ifDoesnExist | readwritemode, 0644); //the last funky number is from the last link, read-write
    // open (not openat) takes const char* path, and or-ed int flags (mode stuff).
    // open returns a file descriptor, -1 for an issue and non-negative if all is good.
    if (fd >= 0) {
        printf("\nAll good, file descriptor is a non-neg!");
    } else {
        printf("\nUnfortunately, fd is not a non-neg.\n");
        perror("problem"); // errno printing/explanation thing
        exit(1);
    }

    return 0;

}

/*

Miscellaneous sources (besides textbook):
https://manpages.ubuntu.com/manpages/questing/en/man1/perror.1.html
https://manpages.ubuntu.com/manpages/questing/en/man2/errno.2freebsd.html
https://manpages.ubuntu.com/manpages/questing/en/man2/open.2freebsd.html
https://manpages.ubuntu.com/manpages/noble/en/man3/access.3posix.html
https://manpages.ubuntu.com/manpages/questing/en/man2/umask.2.html
(Did not add more since the same things were done in the other mini-programs)

*/