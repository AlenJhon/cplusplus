#ifndef CONCRETE_FACTORY_H
#define CONCRETE_FACTORY_H

#include "factory.h"
#include "concrete_product.h"

class BenzFactory : public IFactory {
public:
    ICar* CreateCar() {
        return new BenzCar();
    }
};

class BmwFactory : public IFactory {
public:
    ICar* CreateCar() {
        return new BmwCar();
    }
};

class AudiFactory : public IFactory {
public:
    ICar* CreateCar() {
        return new AudiCar();
    }
};

#endif // CONCRETE_FACTORY_H