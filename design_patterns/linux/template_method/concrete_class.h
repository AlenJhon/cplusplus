#ifndef CONCRETE_CLASS_H
#define CONCRETE_CLASS_H

#include "abstruct_class.h"

class Alibaba : public Company {
public:
    void Interview() {
        std::cout << "alibaba interview\n";
    }
    void Offer() {
        std::cout << "alibaba offer\n";
    }
};

class Tencent : public Company {
public:
    void Interview() {
        std::cout << "Tencent interview\n";
    }
    void Offer() {
        std::cout << "Tencent offer\n";
    }
};

#endif //CONCRETE_CLASS_H