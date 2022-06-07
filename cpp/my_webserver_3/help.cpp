#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "help.h"

void errif(bool condition, const char* errmsg) {
    if (condition) {
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}