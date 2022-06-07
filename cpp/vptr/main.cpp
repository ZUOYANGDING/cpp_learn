#include <iostream>
#include <stdio.h>
#include "help.h"

class Base {
    public:
        Base(){};
        virtual void function1() {
            std::cout<< "Base function1" <<std::endl;
        }
        virtual void function2() {
            std::cout<< "Base function2" <<std::endl;
        }
        ~Base(){};
};

class Derive:public Base {
    public:
        Derive(){};
        void function1() {
            std::cout<< "Derive function1" <<std::endl;
        }
        void function2() {
            std::cout<< "Derive function2" <<std::endl;
        }
        ~Derive(){};
};

class Derive2:public Base {
    public:
        Derive2(){};
        void function1() {
            std::cout<< "Derive2 function1" <<std::endl;
        }
        void function2() {
            std::cout<< "Derive2 function2" <<std::endl;
        }
        ~Derive2(){};
};

FUN_PTR getAddr(void* obj, unsigned int offset) {
    std::cout<< "===========================" <<std::endl;
    // 64位操作系统，占8字节，通过*(unsigned long *)obj取出前8字节，即vptr指针
    void* vptr_addr = (void*) *(unsigned long *)obj;
    printf("vptr address:%p\n", vptr_addr);

    void* vptr_fun = (void*) *((unsigned long *) vptr_addr+offset);
    printf("function address:%p\n", vptr_fun);
    return (FUN_PTR) vptr_fun;
}

int main(int argc, const char* argv[]) {
    Base base;
    Derive derive;
    // pointer to Derive
    Base *base_ptr = new Derive();
    // reference to base
    Base &base_ref = base;
    // reference to derive
    Base &derive_ref = derive;
    Base *base_ptr_2 = new Derive2();
    std::cout<< "base object call base function" <<std::endl;
    base.function1();
    std::cout<< "base reference call base function" <<std::endl;
    base_ref.function1();
    std::cout<< "base pointer call extend function" <<std::endl;
    base_ptr->function1();
    std::cout<< "base reference call extend function" <<std::endl;
    derive_ref.function1();

    FUN_PTR f1 = getAddr(base_ptr, 0);
    (*f1)();
    FUN_PTR f2 = getAddr(base_ptr, 1);
    (*f2)();

    FUN_PTR ff1 = getAddr(base_ptr_2, 0);
    (*ff1)();
    FUN_PTR ff2 = getAddr(base_ptr_2, 1);
    (*ff2)();
    delete base_ptr;
    return 0;
}