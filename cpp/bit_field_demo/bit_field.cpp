#include <iostream>

/**
 * @brief total bits=3*32bit
 * 
 */
struct test {
    unsigned int field1:30;
    // fill up 2 bit for 32bit
    unsigned int       :2;
    unsigned int field2:4;
    // fill up 32 bit
    unsigned int       :0;
    unsigned int field3:3;
};

struct box {
    unsigned int ready      :2;
    unsigned int error      :2;
    unsigned int command    :4;
    unsigned int sector_no  :24;
};

int main(int argc, const char* argv[]) {
    struct test t = {1,3,5};
    std::cout<< t.field1 <<std::endl;
    std::cout<< t.field2 <<std::endl;
    std::cout<< t.field3 <<std::endl;
    std::cout<< sizeof(t) <<std::endl;

    struct box b;
    std::cout<< sizeof(b) <<std::endl;
    b.ready = 1;
    b.error = 3;
    b.command = 5;
    b.sector_no = 7;
    std::cout<< b.ready <<std::endl;
    std::cout<< b.error <<std::endl;
    std::cout<< b.command <<std::endl;
    std::cout<< b.sector_no <<std::endl;
    std::cout<< sizeof(b) <<std::endl;
    int *p = (int*) &b;
    *p = 0;
    std::cout<< b.ready <<std::endl;
    std::cout<< b.error <<std::endl;
    std::cout<< b.command <<std::endl;
    std::cout<< b.sector_no <<std::endl;

    std::cout<< sizeof(unsigned int) <<std::endl;
}