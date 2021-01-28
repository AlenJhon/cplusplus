#include <iostream>

using namespace std;

struct Base{
    virtual void foo();
};

struct A : Base{
    void foo() final;
    // void bar() final;//不是虚函数不能final修饰
};

struct B final:A{
    // void foo() override;//不能被重写final方法
};

struct C final{
    int a_{1};
    int b_{2};
};

// struct D : C {
// }


//私有构造+友元类+虚继承
template<typename T>
class BaseT{
public:
    friend T;
private:
    BaseT(){}
    ~BaseT(){}
};
class FinalClass : virtual public BaseT<FinalClass>{
public:
    FinalClass(){}
    ~FinalClass(){}
    void Print(){cout << "Print" << endl;}
};

//不能继承
// class XXFromFinalClass : public FinalClass {
// public:
//     XXFromFinalClass(){}
//     ~XXFromFinalClass(){}
// };


int main(){
    // struct B b;
    // struct C c;
    // cout << c.a_ << " " << c.b_ << endl;

    FinalClass a;
    a.Print();

    return 0;
}