#pragma once
#include <iostream>
// abstract class
class Base {
    public:
        // constructor can not be virtual
        Base() {
            std::cout<< "constructor of base" <<std::endl;
        };
        // destructor can be virturl
        virtual ~Base() {std::cout<< "desctructor of base" <<std::endl;}
        virtual int getParam() const =0;
        virtual void setParam(int a)=0;
        virtual void add(int a)=0;
        virtual void sub(int a)=0;
        virtual void print() const = 0;
};