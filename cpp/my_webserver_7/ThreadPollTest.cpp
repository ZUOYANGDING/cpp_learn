#include "src/ThreadPoll.h"
#include <string>
#include <iostream>

void print(const char* a, std::string b) {
    std::cout<< "run func1" <<std::endl;
    std::cout<< a << b <<std::endl;
}

void plus(int a, double b) {
    std::cout<< "run func2" <<std::endl;
    std::cout<< a+b <<std::endl;
}

void minus(int a , int b) {
    std::cout<< "run func3" <<std::endl;
    std::cout<< a-b <<std::endl;
}

int main() {
    ThreadPoll *poll = new ThreadPoll();
    std::function<void()> func1 = std::bind(print, "hello ", "world");
    std::function<void()> func2 = std::bind(plus, 1, 2.0);
    std::function<void()> func3 = std::bind(minus, 3, 4);
    std::cout<< "add func1" <<std::endl;
    poll->add(func1);
    std::cout<< "add func2" <<std::endl;
    poll->add(func2);
    std::cout<< "add func3" <<std::endl;
    poll->add(func3);
    delete poll;
    return 0;
}