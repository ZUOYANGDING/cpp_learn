#include <iostream>
#include <unistd.h>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main(int argc, const char* argv[]) {
    int a = *argv[1] - '0';
    int b = *argv[2] - '0';
    swap(a, b);
    std::cout<< a << "    " << b <<std::endl;
    return 0;
}