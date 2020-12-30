#include <iostream>
#include "concrete_factory.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif//SAFE_DELETE

int main() {
    std::cout << "start factory methods test .\n";

    //IFactory* ifact = new BenzFactory();
    IFactory* ifact = IFactory::CreateFactory(IFactory::BENZ_FACTORY);
    ICar* icar = ifact->CreateCar();
    icar->Name();

    SAFE_DELETE(ifact);
    SAFE_DELETE(icar);

    ifact = IFactory::CreateFactory(IFactory::BMW_FACTORY);
    icar = ifact->CreateCar();
    icar->Name();

    SAFE_DELETE(ifact);
    SAFE_DELETE(icar);


    ifact = IFactory::CreateFactory(IFactory::AUDI_FACTORY);
    icar = ifact->CreateCar();
    icar->Name();

    SAFE_DELETE(ifact);
    SAFE_DELETE(icar);

    return 0;
}
