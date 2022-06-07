#include <iostream>
#include "../apue.h"
#define BUFFSIZE 2048

int main(void) {
    int n;
    char buff[BUFFSIZE];
    while ((n=read(STDIN_FILENO, buff, BUFFSIZE))>0) {
        if (write(STDOUT_FILENO, buff, n)!=n) {
            std::cout<< "write error" <<std::endl;
        }
    }
    if (n < 0) {
        std::cout<< "read error" <<std::endl;
    }
    exit(0);
}