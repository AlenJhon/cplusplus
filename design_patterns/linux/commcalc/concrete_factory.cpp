#include "ifactory.h"
#include "concrete_operation.h"

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