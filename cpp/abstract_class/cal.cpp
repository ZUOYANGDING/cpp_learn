#include <iostream>
#include "cal.h"

Cal::Cal() {
    std::cout<< "cal constructor" <<std::endl;
}

Cal::Cal(int a){
    std::cout<< "cal constructor" <<std::endl;
    this->param = a;
}

Cal::~Cal() {
    std::cout<< "cal destructor" <<std::endl;
}

void Cal::setParam(int a) {
    this->param = a;
}

void Cal::add(int a) {
    this->param += a;
}

void Cal::sub(int a) {
    this->param -= a;
}

int Cal::getParam() const{
    return this->param;
}

void Cal::print() const{
    std::cout<< this->getParam() <<std::endl;
}

