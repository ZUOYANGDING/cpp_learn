#include <iostream>
#include "cal.h"

int main(int argc, const char* argv[]) {
    std::cout<< "===========cal 1=========" <<std::endl;
    Cal cal1;
    cal1.setParam(1);
    cal1.add(2);
    cal1.print();
    cal1.sub(1);
    cal1.print();
    std::cout<< "===========cal 2=========" <<std::endl;
    Cal cal2(0);
    cal1.setParam(1);
    cal1.add(2);
    cal1.print();
    cal1.sub(1);
    cal1.print();
    std::cout<< "==========cal 3===========" <<std::endl;
    Base *ptr = new Cal(3);
    ptr->add(1);
    ptr->print();
    ptr->sub(1);
    ptr->print();
    // 通过pointer调用abstract类的派生类，需要显式调用析构函数, 或通过delete隐式调用对象的析构函数(二者不可同时使用，否则调用两次析构函数会segment fault)
    // ptr->~Base();
    delete ptr;
}