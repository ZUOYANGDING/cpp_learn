#include <iostream>
#include "../apue.h"

int main() {
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        std::cout<< "std input cannot seek" <<std::endl;
    } else {
        std::cout<< "std input can seek" <<std::endl;
        exit(0);
    }
}