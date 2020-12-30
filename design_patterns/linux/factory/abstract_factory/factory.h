#ifndef FACTORY_H
#define FACTORY_H

#include "product.h"

class IFactory {
public:
    enum FACTORY_TYPE {
        BENZ_FACTORY,
	BMW_FACTORY,
	AUDI_FACTORY
    };
    virtual ICar* CreateCar() = 0;
    static IFactory* CreateFactory(FACTORY_TYPE type);
};

#endif // FACTORY_H
