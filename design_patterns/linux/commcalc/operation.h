#ifndef OPERATION_H_
#define OPERATION_H_

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