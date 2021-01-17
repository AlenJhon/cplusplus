#ifndef IFACTORY_H_
#define IFACTORY_H_

#include "operation.h"
/**
 * 工厂声明文件，定义了不同生产类型
*/

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