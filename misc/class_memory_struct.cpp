#include <iostream>
#include <cstdio>

using namespace std;

#define CASE1 0
#define CASE2 1
#define CASE3 0

#if CASE1
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
#elif CASE2

//虚拟继承 case 2
class A {
public:
    int a {100};
};

class B : virtual public A {
public:
    int b {10};
};

#elif CASE3

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
#if CASE3
    B b;
    cout << "case 2: " << sizeof(b) << endl;

#elif CASE2

    //case 2
    /*
    * 8Bytes -> virtal table(8Bytes=4Bytes=current vptr offset=0 + 4Bytes=virtual parrent A.a in b class offset=8) , 
    * 4Bytes=b=10, 
    * 4Bytes=a=100
    * 
    * 
    * case 2: 16
    * case 2: &b =   0x7fff9ffb2ea0
    * case 2: &b.a = 0x7fff9ffb2eac
    * case 2: &b.b = 0x7fff9ffb2ea8

    */
    B b;
    cout << "case 2: sizeof(int)=" << sizeof(int) << endl;
    cout << "case 2: " << sizeof(b) << endl; 
    cout << "case 2: &b = " << &b << endl;
    cout << "case 2: &b.a = " << &(b.a) << endl;
    cout << "case 2: &b.b = " << &(b.b) << endl;
    // cout << "case 2: sizeof(long) = " << sizeof(long) << endl;
    // printf("(long *)&b=%p", *(long *)&b);
    // cout << "case 2: *(int *)&b = " << *(int *)&b << endl;
    // cout << "case 2: *(((int *)&b) + 1) = " << *(((int *)&b) + 1) << endl;

#elif CASE1
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
#endif
    return 0;
}

// 以下代码是在visual studio中 /d1 reportSingleClassLayoutACheckLayout 查看的结果
#if 0
class ACheckLayout {
public:
    int a{ 100 };
    int b{ 100 };
    virtual void Show() { cout << "Show." << endl; }
    virtual void Show2() { cout << "Show." << endl; }
};
#elif 0
class CBase
{
public:
    int a{100};
    int b{100};
};
class ACheckLayout : public CBase
{
public:
    int aa{100};
    int bb{100};
};
#elif 0

class CBase
{
public:
    int a{100};
    int b{100};
};
class ACheckLayout : public virtual CBase
{
public:
    int aa{100};
    int bb{100};
    int a{22222};
    //virtual void Show() { cout << "Show." << endl; }
    //virtual void Show2() { cout << "Show." << endl; }
};
/*
1>class ACheckLayout	size(24):
1>	+---
1> 0	| {vbptr}
1> 4	| aa
1> 8	| bb
1>12	| a
1>	+---
1>	+--- (virtual base CBase)
1>16	| a
1>20	| b
1>	+---
1>
1>ACheckLayout::$vbtable@:
1> 0	| 0
1> 1	| 16 (ACheckLayoutd(ACheckLayout+0)CBase)
1>vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
1>           CBase      16       0       4 0
*/

#elif 0
class CBase {
public:
    int a{ 100 };
    int b{ 100 };
    virtual void Show() {}
};
class ACheckLayout : public virtual CBase {
public:
    int aa{ 100 };
    int bb{ 100 };
    int a{ 22222 };
    //virtual void Show() { cout << "Show." << endl; }
    //virtual void Show2() { cout << "Show." << endl; }
};

/*
1>class ACheckLayout	size(28):
1>	+---
1> 0	| {vbptr}
1> 4	| aa
1> 8	| bb
1>12	| a
1>	+---
1>	+--- (virtual base CBase)
1>16	| {vfptr}
1>20	| a
1>24	| b
1>	+---
1>
1>ACheckLayout::$vbtable@:
1> 0	| 0
1> 1	| 16 (ACheckLayoutd(ACheckLayout+0)CBase)
1>
1>ACheckLayout::$vftable@:
1>	| -16
1> 0	| &CBase::Show
1>vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
1>           CBase      16       0       4 0
*/

#elif 0

class ABase {
public:
    int a{ 100 };
};
class BLeft : public virtual ABase {
public:
    int b{ 100 };
};
class CRight : public virtual ABase {
public:
    int c{ 100 };
};

class ACheckLayout : public BLeft, public CRight {
public:
    int d{ 22222 };
};

/*
1>class ACheckLayout	size(24):
1>	+---
1> 0	| +--- (base class BLeft)
1> 0	| | {vbptr}
1> 4	| | b
1>	| +---
1> 8	| +--- (base class CRight)
1> 8	| | {vbptr}
1>12	| | c
1>	| +---
1>16	| d
1>	+---
1>	+--- (virtual base ABase)
1>20	| a
1>	+---
1>
1>ACheckLayout::$vbtable@BLeft@:
1> 0	| 0
1> 1	| 20 (ACheckLayoutd(BLeft+0)ABase)
1>
1>ACheckLayout::$vbtable@CRight@:
1> 0	| 0
1> 1	| 12 (ACheckLayoutd(CRight+0)ABase)
1>vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
1>           ABase      20       0       4 0
*/
#endif