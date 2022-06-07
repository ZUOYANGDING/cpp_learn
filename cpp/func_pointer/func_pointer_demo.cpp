#include <iostream>
#include "func_pointer.h"

void foo1() {
    std::cout<< "in func foo1" <<std::endl;
}

// return type is function pointer
FUNC_PTR foo2() {
    return foo1;
}

int main() {
    FUNC_PTR_RET p = foo2;
    p()();
    return 0;
}