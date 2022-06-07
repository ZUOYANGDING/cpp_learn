#include <iostream>
#include <unistd.h>

enum weekday {
  Sun, Mon, Tues, Wed, Thurs, Fri, Sat  
};

int main(int argc, const char* argv[]) {
    enum weekday wek=Mon;
    std::cout<< wek <<std::endl;
    for (int i=wek; i!=Sat; i++) {
        std::cout<< i <<std::endl;
    }
    return 0;
}