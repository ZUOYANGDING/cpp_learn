#include <iostream>
#include "classroom.h"

int main(int argc, const char* argv[]) {
    int indicator;
    std::cin>>indicator;
    if (indicator==0){
        // static parm life cycle continues to the end of main
        static Classroom classroom(100);
    } else {
        Classroom classroom(50);
    }
    std::cout<< "end of main" <<std::endl;
    return 0;
}