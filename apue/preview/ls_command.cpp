#include <iostream>
#include <dirent.h>
#include "../apue.h"

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *dirp;
    
    if (argc!=2) {
        std::cout<<"usage: ls dirctory_name"<<std::endl;
    }

    if ((dir=opendir(argv[1]))==nullptr) {
        std::cout<<"cannot open directory: "<< argv[1] <<std::endl;
    }
    while ((dirp=readdir(dir))!=nullptr) {
        std::cout<< dirp->d_name <<std::endl;
    }
    closedir(dir);
    exit(0);
}