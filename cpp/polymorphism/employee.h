#pragma once
#include <iostream>
#include "base.h"
class Employee: public Base{
    protected:
        std::string name;
        std::string phone;
        double salary;
        int age;
    public:
        Employee(){};
        // since Employee will be extend, destructor must be virtural. Otherwise after dynamic_cast, destructor of extender will not be called
        virtual ~Employee(){
            std::cout<< "desctructor of Employee" <<std::endl;
        };
        void setInfo(const std::string name, int age, const std::string phone);
        void setSalary(double salary);
        void getInfo() const;
        double getSalary() const;
};

class Manager: public Employee{
    private:
        std::string name;
        std::string phone;
        double salary;
        int age;
    public:
        Manager(){};
        void promote(Employee* stuff, double salary);
        ~Manager(){
            std::cout<< "desctructor of Manager" <<std::endl;
        };
};

class Engineer: public Employee {
    private:
        std::string name;
        std::string phone;
        int age;
    public:
        double salary;
        Engineer(){};
        void work() const;
        ~Engineer(){
            std::cout<< "desctructor of Engineer" <<std::endl;
        };
};

class Seller:public Employee {
    private:
        std::string name;
        std::string phone;
        int age;
        double salary;
    public:
        Seller(){};
        ~Seller() {
            std::cout<< "desctructor of Seller" <<std::endl;
        };
        void sell() const;
};