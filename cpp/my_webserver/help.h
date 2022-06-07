#ifndef _HELP_H_
#define _HELP_H_
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
void errif(bool condition, const char *errmsg) {
    if (condition) {
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}

void setnonBlocking(int fd) {
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}
#endif
