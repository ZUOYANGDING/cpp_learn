#include "employee.h"

int main(int argc, const char* argv[]) {
    Employee* manager = new Manager();
    Employee* engineer = new Engineer();
    Employee* seller = new Seller();
    manager->setInfo("test manager", 20, "xxx-xxx-xxxx");
    manager->setSalary(100);
    manager->getInfo();

    engineer->setInfo("test engineer", 25, "xxx-xxx-xxxx");
    engineer->setSalary(200);
    engineer->getInfo();
    dynamic_cast<Engineer*>(engineer)->work();
    dynamic_cast<Manager*>(manager)->promote(engineer, 200);
    engineer->getInfo();

    seller->setInfo("test seller", 25, "xxx-xxx-xxxx");
    seller->setSalary(100);
    seller->getInfo();
    dynamic_cast<Seller*>(seller)->sell();
    dynamic_cast<Manager*>(manager)->promote(seller, 200);
    seller->getInfo();
    delete manager;
    delete engineer;
    delete seller;
}