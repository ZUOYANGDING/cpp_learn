#include <stdio.h>

int main(int argc, const char* argv[]) {
    // without volatile, const int cannot be manipulate
    volatile const int local = 10;
    int *ptr = (int*) &local;
    printf("init value for local %d\n", local);
    *ptr = 100;
    printf("modified value for local %d\n", local);
    return 0;
}