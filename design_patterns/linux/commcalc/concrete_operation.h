#ifndef CONCRETE_OPERATION_H_
#define CONCRETE_OPERATION_H_

#include "operation.h"

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