#ifndef IFACTORY_H_
#define IFACTORY_H_

#include "operation.h"

class Factory {
public:
    enum OP_TYPE {
        ADD,
        SUB,
        MUL,
        DIV
    };
    static Operation* CreateOperation(OP_TYPE op);
};

#endif //IFACTORY_H_