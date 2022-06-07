#include <iostream>
#include <unistd.h>
#include "student.h"

int main(int argc, const char* argv[]){
    Classroom class_room(100);
    class_room.sub(50, 10);
    std::cout<< class_room.getScore(50) <<std::endl;
}