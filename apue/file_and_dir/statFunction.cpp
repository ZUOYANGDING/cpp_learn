#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{   
    /* code */
    struct stat buff;
    if (argc <  2) {
        std::cout<< "at least 2 args" << std::endl;
        exit(0);
    }
    for (int i=1; i<argc; ++i) {
        std::cout<< argv[i] <<std::endl;
        if (lstat(argv[i], &buff) < 0) {
            std::cout<< "lstat error" <<std::endl;
            continue;
        }
        if(S_ISREG(buff.st_mode)) {
            std::cout<< "regular" <<std::endl;
            std::cout<< buff.st_uid <<std::endl;
            std::cout<< buff.st_gid <<std::endl;
        } else if (S_ISDIR(buff.st_mode)) {
            std::cout<< "directory" <<std::endl;
        } else if (S_ISCHR(buff.st_mode)) {
            std::cout<< "character special file" <<std::endl;
        } else if (S_ISBLK(buff.st_mode)) {
            std::cout<< "block special file" <<std::endl;
        } else if (S_ISFIFO(buff.st_mode)) {
            std::cout<< "pipe of FIFO" <<std::endl;
        } else if (S_ISLNK(buff.st_mode)) {
            std::cout<< "symbolic link" <<std::endl;
        } else if (S_ISSOCK(buff.st_mode)) {
            std::cout<< "socket" <<std::endl;
        } else {
            std::cout<< "unknown" <<std::endl;
        }
        
    }
    exit(0);
}
