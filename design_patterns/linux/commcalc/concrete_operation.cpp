#include "concrete_operation.h"

/**
 * 具体产品实现文件，对GetResult接口重写
*/

double Add::GetResult() {
    return GetNumberA() + GetNumberB();
}


double Sub::GetResult() {
    return GetNumberA() - GetNumberB();
}

double Mul::GetResult() {
    return GetNumberA() * GetNumberB();
}

double Div::GetResult() {
    if (GetNumberB() == 0) {
        throw("除数不能是零");//抛出异常
        return 0;
    }
    return GetNumberA() / GetNumberB();
}