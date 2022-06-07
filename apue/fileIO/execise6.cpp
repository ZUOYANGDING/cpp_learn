#include <iostream>
#include <fcntl.h>
#include "../apue.h"

#define BUFFER_SIZE 3

int main() {
   int fd;
   char buffer[BUFFER_SIZE];
   if ((fd = open("temp.out", O_RDWR & O_APPEND)) <0) {
       std::cerr<< "open failed" <<std::endl;
   }
   int offSet = lseek(fd, 3, SEEK_CUR);
   int var;
   if ((var=read(fd, buffer, BUFFER_SIZE)) != BUFFER_SIZE) {
       std::cerr<< "read failed: " <<  var << std::endl;
   } else {
       std::cout<< buffer <<std::endl;
   }
   exit(0);
}
