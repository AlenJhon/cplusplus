#include "factory.h"
#include "concrete_factory.h"


IFactory* IFactory::CreateFactory(FACTORY_TYPE type) {
    IFactory* ifact = nullptr;
    switch (type) {
    case BENZ_FACTORY:
        ifact = new BenzFactory();
        break;
    case BMW_FACTORY:
        ifact = new BmwFactory();
        break;
    case AUDI_FACTORY:
        ifact = new AudiFactory();
        break;
    default:
	    ifact = nullptr;
        break;
    }
    return ifact;
}
