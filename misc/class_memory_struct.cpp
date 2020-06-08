#include <iostream>
#include <cstdio>

using namespace std;

#if 0
//单继承 case 1
class A {
public:
    A(int n):a(n){}
    void Show(){
        printf("a:%d", a);
    }
    int a;
};

class B : public A {
public:
    B (int n):b(n),A(100){}
    void Show() {
        printf("Show a=%d, b=%d", a, b);
    }
    int b;
};
#elif 0

//虚拟继承 case 2
class A {
public:
    int a {100};
};

class B :public virtual A {
public:
    int b {10};
};

#elif 1

// 多态 case 3
class A {
public:
    virtual void Show() {
        cout << "a :" << a << endl;
    }
    int a{100};
};

class B : public A {
public:
    virtual void Show() {
        cout << "b :" << b << endl;
    }
    int b = {10};
};


#endif



int main() {
    // case 3
    B b;
    cout << "case 2: " << sizeof(b) << endl; 




    //case 2
    /*
    * 8Bytes -> virtal table(8Bytes=4Bytes=current vptr offset=0 + 4Bytes=virtual parrent A.a in b class offset=8) , 
    * 4Bytes=b=10, 
    * 4Bytes=a=100
    */
    // B b;
    // cout << "case 2: " << sizeof(b) << endl; // == 16
    // cout << "case 2: &b = " << &b << endl;
    // cout << "case 2: &b.a = " << &b.a << endl;
    // cout << "case 2: &b.b = " << &b.b << endl;
    // cout << "case 2: sizeof(long) = " << sizeof(long) << endl;
    // printf("(long *)&b=%p", *(long *)&b);
    // cout << "case 2: *(int *)&b = " << *(int *)&b << endl;
    // cout << "case 2: *(((int *)&b) + 1) = " << *(((int *)&b) + 1) << endl;

    // B b(10);
    // cout << "case 1:     " << sizeof(b) << endl;
    // cout << "case 1: &b :" << &b << endl;
    // cout << "case 1: &b.a :" << &(b.a) << ", *(int*)&(b.a) =" << *(int *)&(b.a) << endl;
    // cout << "case 1: &b.b :" << &(b.b) << ", *(int*)&(b.b) =" << *(int *)&(b.b) << endl;
    // cout << "case 1: " ;
    // b.Show();
    // cout << endl;
    /*
case 1:     8
case 1: &b :0x7ffdd69cf8e0
case 1: &b.a :0x7ffdd69cf8e0, *(int*)&(b.a) =100
case 1: &b.b :0x7ffdd69cf8e4, *(int*)&(b.b) =10
case 1: Show a=100, b=10
    */
    return 0;
}