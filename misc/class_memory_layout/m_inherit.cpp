#include <iostream>

using namespace std;

class A {
public:
    virtual void print() {
        cout << "A print\n";
    }
};

class B {
public:
    virtual void print() {
        cout << "B print\n";
    }
};

class C :public B , public A{
public:
    // virtual void print() {
    //     cout << "C print\n";
    // }
    //option keyword virtual
    void print() {
        cout << "C print function\n";
    }
};

typedef void (*fn)();

int main() {
    C c;
    cout << "sizeof(long*) = " << sizeof(long*) << endl;
    cout << sizeof(c) << endl;
    long *p = (long*)&c;
    // p += 1; //如果不执行这行指令调用的是第一个虚表指针指向的虚表函数
    fn f = (fn)*(long*)(*p);
    f();





    return 0;
}