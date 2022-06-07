#include <iostream>
#include "classroom.h"

Classroom::Classroom(int i) {
    index = i;
    std::cout<< "in constructor" <<std::endl;
}

Classroom::~Classroom() {
    std::cout<< "in distructor" <<std::endl;
}