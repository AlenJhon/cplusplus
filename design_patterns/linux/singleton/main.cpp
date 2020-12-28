#include <iostream>
#include "singleton.h"

int main() {
    Singleton* inst1 = Singleton::GetInstence();
    Singleton* inst2 = Singleton::GetInstence();
    if (inst1 == inst2) {
        std::cout << "inst1==inst2\n";
    }
    return 0;
}