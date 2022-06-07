#include <iostream>
#include "person.h"

int main(int argc, const char* argv[]) {
    Person p1("person1", 10, Person::Sex_type::_Male_);
    Person p2(Person::Sex_type::_Female_);
    p2.setName("person2");
    p2.setAge(20);
    std::cout<< p1.getName() << ": " << p1.getAge() <<std::endl;
    std::cout<< p2.getName() << ": " <<p2.getAge() <<std::endl;
    return 0;
}