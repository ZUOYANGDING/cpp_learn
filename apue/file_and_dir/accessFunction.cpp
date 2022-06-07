#include <fcntl.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout<< "usage: accessFunction <pathname>" <<std::endl;
        exit(-1);
    }
    if (access(argv[1], R_OK) < 0) {
        std::cout<< "have no read permission"<< std::endl;
        exit(-1);
    } else {
        std::cout<< "read permission"<< std::endl;
        if (open(argv[1], O_RDONLY) < 0) {
            std::cout<< "open failed" <<std::endl;
        } else {
            std::cout<< "open ok" <<std::endl;
        }
    }
    
}