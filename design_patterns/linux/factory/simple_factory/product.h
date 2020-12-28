#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class ICar {
public:
    virtual std::string Name() = 0;
};

#endif //PRODUCT_H