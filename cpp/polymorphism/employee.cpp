#include <iostream>
#include "employee.h"

void Employee::setInfo(const std::string name, int age, const std::string phone){
    this->name = name;
    this->age = age;
    this->phone = phone;
}

void Employee::getInfo() const {
    std::cout<< "name: " << this->name <<std::endl;
    std::cout<< "age: " << this->age <<std::endl;
    std::cout<< "phone:" << this->phone <<std::endl;
    std::cout<< "salary: " << this->salary <<std::endl;
}

void Employee::setSalary(double salary) {
    this->salary = salary;
}

double Employee::getSalary() const {
    return this->salary;
}

void Manager::promote(Employee* stuff, double salary) {
    double baseSalary = stuff->getSalary();
    baseSalary += salary;
    stuff->setSalary(baseSalary);
}

void Engineer::work() const {
    std::cout<< "start work" <<std::endl;
}

void Seller::sell() const {
    std::cout<< "start sell" <<std::endl;
}

