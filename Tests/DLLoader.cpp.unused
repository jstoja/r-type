#include <iostream>
#include <string>
#include "Debug.h"
#include "Library.h"

void    myprint();

int main()
{
    std::string marseille("./marseille.so");
    Library    lib(marseille);
    
    lib.load();
    std::cout << lib.getErrorString() << std::endl;
    void (*ptr)() = reinterpret_cast<void (*)()>(lib.resolve("myprint"));
    std::cout << lib.getErrorString() << std::endl;
    (*ptr)();
    return 0;
}
