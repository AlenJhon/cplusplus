#include "concrete_operation.h"

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
        return 0;//抛出异常
    }
    return GetNumberA() / GetNumberB();
}