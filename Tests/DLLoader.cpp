#include <iostream>
#include <string>
#include "Debug.h"
#include "DLLoader.h"

void    myprint();

int main()
{
    std::string marseille("./marseille.so");
    DLLoader    dll(marseille);
    
    dll.load();
    std::cout << dll.getErrorString() << std::endl;
    void (*ptr)() = reinterpret_cast<void (*)()>(dll.resolve("myprint"));
    std::cout << dll.getErrorString() << std::endl;
    (*ptr)();
    return 0;
}
