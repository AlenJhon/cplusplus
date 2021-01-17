#ifndef CONCRETE_OPERATION_H_
#define CONCRETE_OPERATION_H_

#include "operation.h"

/**
 * 具体产品声明，统一继承自基类Operation，对GetResult接口重写
*/

class Add : public Operation {
public:
    double GetResult();
};

class Sub : public Operation {
public:
    double GetResult();
};

class Mul : public Operation {
public:
    double GetResult();
};

class Div : public Operation {
public:
    double GetResult();
};

#endif // CONCRETE_OPERATION_H_