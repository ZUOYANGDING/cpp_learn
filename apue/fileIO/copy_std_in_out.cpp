#include <fcntl.h>
#include <iostream>
#include "../apue.h"

#define BUFFSIZE 1024

int main() {
    int n;
    char buff[BUFFSIZE];
    
    while ((n=read(STDIN_FILENO, buff, BUFFSIZE))>0) {
        if (write(STDOUT_FILENO, buff, n) != n) {
            std::cerr<< "write error" <<std::endl;
        }
    }
    if (n < 0) {
        std::cerr << "read error" <<std::endl;
    }
}