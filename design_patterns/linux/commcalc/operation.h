#ifndef OPERATION_H_
#define OPERATION_H_

/**
 * 定义计算器的接口方法主要是GetResult（）方便扩展成不同类型的计算
 * 其它方法是一个计算器的基础能力定义（设置操作数，获取操作数）
*/

class Operation {
public:
    Operation();
    virtual ~Operation();

public:
    void SetNumberA(double a = 0);
    double GetNumberA();

    void SetNumberB(double b = 0);
    double GetNumberB();

    virtual double GetResult();

private:
    double a_;
    double b_;
};

#endif //OPERATION_H_