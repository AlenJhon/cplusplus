#ifndef FACTORY_H
#define FACTORY_H

#include "concrete_product.h"

class Factory {
public:
    enum CAR_TYPE {
        BENZ_CAR,
        BMW_CAR,
        AUDI_CAR
    };
    ICar* CreateCar(CAR_TYPE type) {
        ICar* pcar = nullptr;
        switch (type)
        {
        case CAR_TYPE::BENZ_CAR:
            pcar = new BenzCar();
            break;
        case CAR_TYPE::BMW_CAR:
            pcar = new BmwCar();
            break;
        case CAR_TYPE::AUDI_CAR:
            pcar = new AudiCar();
            break;
        default:
            break;
        }
        return pcar;
    }
};

#endif //FACTORY_H