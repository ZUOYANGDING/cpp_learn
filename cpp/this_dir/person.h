#pragma once
#include <string>

class Person{
    public:
        typedef enum {
            _Male_=0,
            _Female_
        }Sex_type;
        Person(const std::string name, int age, Sex_type sex);
        Person(Sex_type sex);
        ~Person();
        void setAge(int age);
        void setName(const std::string name);
        const std::string getName() const;
        const int getAge() const;
    private:
        std::string name;
        int age;
        Sex_type sex;
};