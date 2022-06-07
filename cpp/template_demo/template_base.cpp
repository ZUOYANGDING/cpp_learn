#include <iostream>
#include "template_base.h"

template<class T> A<T>::A(T _a, T _b){
    this->a = _a;
    this->b = _b;
};
template<class T> A<T>::~A(){};

template<class T> void A<T>::swap() {
    T temp = this->a;
    this->a = this->b;
    this->b = temp;
}

template<class T> void A<T>::print() const{
    std::cout<< "a: " << this->a << " b: " << this->b <<std::endl; 
}

int main() {
    A<int> a(3, 5);
    a.print();
    a.swap();
    a.print();

    A<double> b(2.15, 3.15);
    b.print();
    b.swap();
    b.print();
    return 0;
}
