#ifndef CONCRTE_PRODUCT_H
#define CONCRTE_PRODUCT_H

#include "product.h"
#include <iostream>

class BenzCar : public ICar {
public:
    void Name() {
        std::cout << "BenzCar\n";
    }
};

class BmwCar : public ICar {
public:
    void Name() {
        std::cout << "BmwCar\n";
    }
};

class AudiCar : public ICar {
public:
    void Name() {
        std::cout << "AudiCar\n";
    }
};

#endif //CONCRTE_PRODUCT_H