#ifndef FACTORY_H
#define FACTORY_H

#include "product.h"

class IFactory {
public:
    virtual ICar* CreateCar() = 0;
};

#endif // FACTORY_H