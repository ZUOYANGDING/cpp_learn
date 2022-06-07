#include <iostream>
#include <string>
#include <fcntl.h>
#include "../apue.h"

int main() {
    int fd;
    char s1[] = "ABCDEFG";
    char s2[] = "HIJKLMN";
    if ((fd = creat("file.hole", FILE_MODE)) < 0) {
        std::cerr<< "create file failed" <<std::endl;
    }
    if (write(fd, s1, 7)!=7) {
        std::cerr<< "write into file failed" <<std::endl;
    } else {
        std::cout<< "offset is: " << lseek(fd, 0, SEEK_CUR) << std::endl;
    }
    if (lseek(fd, 16384, SEEK_SET) == -1) {
        std::cerr << "jump failed" <<std::endl;
    } else {
        std::cout<< "offset is: " << lseek(fd, 0, SEEK_CUR) << std::endl;
    }
    if (write(fd, s2, 7)!=7) {
        std::cerr<< "write into file failed" <<std::endl;
    } else {
        std::cout<< "offset is: " << lseek(fd, 0, SEEK_CUR) << std::endl;
    }
    exit(0);
}