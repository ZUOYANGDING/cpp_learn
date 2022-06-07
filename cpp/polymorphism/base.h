#pragma once
#include <string>

class Base {
    public:
        Base(){}
        virtual void setInfo(const std::string name, int age, const std::string phone)=0;
        virtual void getInfo() const = 0;
        ~Base(){};
};