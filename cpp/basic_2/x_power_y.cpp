#include <iostream>
#include <unistd.h>

double power(int x, int y) {
    if (y==0) {
        return 1;
    }
    double temp = power(x, y/2);
    if (y%2 == 0) {
        return temp*temp;
    } else {
        return x*temp*temp;
    }
}



// x^n = x^(n/2) * x^(n/2)
int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout<< "not enough params" <<std::endl;
    }
    int x = *argv[1] - '0';
    int y = *argv[2] - '0';
    std::cout<< power(x, y) <<std::endl;
    pause();
    return 0;    
}

