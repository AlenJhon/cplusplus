#include "operation.h"

/**
 * 对Operation类具体实现
*/

Operation::Operation():a_(0),b_(0) {}

Operation::~Operation() {}

void Operation::SetNumberA(double a) {
    a_ = a;
}

void Operation::SetNumberB(double b) {
    b_ = b;
}

double Operation::GetNumberA() {
    return a_;
}

double Operation::GetNumberB() {
    return b_;
}

//默认计算方式
double Operation::GetResult() {
    return 0;
}