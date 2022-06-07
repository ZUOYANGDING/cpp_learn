#include "person.h"
#include <string>

Person::Person(const std::string name, int age, Sex_type sex) {
    this->name = std::string(name);
    this->age = age;
    this->sex = sex;
}

Person::Person(Sex_type sex){
    this->sex = sex;
}

Person::~Person(){}

const std::string Person::getName() const{
    return this->name;
}

const int Person::getAge() const {
    return this->age;
}

void Person::setName(const std::string name) {
    this->name = std::string(name);
}

void Person::setAge(int age) {
    this->age = age;
}

