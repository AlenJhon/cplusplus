#include "concrete_operation.h"
// #include "concrete_factory.h"
#include "ifactory.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif//SAFE_DELETE

int main() {

    // Add calc;
    // calc.SetNumberA(10);
    // calc.SetNumberB(20);
    // std::cout << calc.GetResult() << std::endl;

    // Sub calc;
    // calc.SetNumberA(10);
    // calc.SetNumberB(20);
    // std::cout << calc.GetResult() << std::endl;

    // Mul calc;
    // calc.SetNumberA(10);
    // calc.SetNumberB(20);
    // std::cout << calc.GetResult() << std::endl;

    // Div calc;
    // calc.SetNumberA(10);
    // calc.SetNumberB(20);
    // std::cout << calc.GetResult() << std::endl;

    Operation* op = Factory::CreateOperation(Factory::ADD);
    op->SetNumberA(10);
    op->SetNumberB(20);
    std::cout << op->GetResult() << std::endl;

    SAFE_DELETE(op);

    return 0;
}