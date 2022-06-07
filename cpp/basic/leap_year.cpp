#include <iostream>
#include <unistd.h>
int main(int argc, char const *argv[]) {
    std::cout<< "input year:"<<std::endl;
    int year;
    std::cin>>year;
    if (((year%4==0)&&(year%100!=0)) || (year%400==0)) {
        std::cout<< "leap year" <<std::endl;
    } else {
        std::cout<< "not leap year" <<std::endl;
    }
    pause();
    return 0;
}