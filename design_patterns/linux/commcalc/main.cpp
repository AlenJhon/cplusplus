#include "concrete_operation.h"
// #include "concrete_factory.h"
#include "ifactory.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif//SAFE_DELETE

int main() {

    //没加入工厂方法的使用方式
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

    //加入工厂方法的使用方式
    Operation* op = Factory::CreateOperation(Factory::ADD);//针对类型生产计算器
    op->SetNumberA(10);
    op->SetNumberB(20);
    std::cout << op->GetResult() << std::endl;//根据不同类型的计算器，得出不一样的结果

    SAFE_DELETE(op);//释放对象

    return 0;
}