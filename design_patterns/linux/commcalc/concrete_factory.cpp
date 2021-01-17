#include "ifactory.h"
#include "concrete_operation.h"

/**
 * 对工厂方法的实现，针对参数提供的不同生产类型就行new出不同对象
*/

Operation* Factory::CreateOperation(OP_TYPE op) {
    Operation* oper = nullptr;
    switch (op)
    {
    case ADD:
        oper = new Add();
        break;
    case SUB:
        oper = new Sub();
        break;
    case MUL:
        oper = new Mul();
        break;
    case DIV:
        oper = new Div();
        break;
    
    default:
        break;
    }
    return oper;
}