// #include <iostream>
// #include "virtual_inherit.h"
// using namespace std;
#include <cstdio>
// #include "public_inherit.h"
#include "constructor.h"

#if 0
//单一类 没有继承关系，没有虚函数
class CaseA{
    int a_{12};
    int b_{21};
};

//单一类 没有继承关系，有虚函数
class CaseB {
    int a_{12};
    int b_{21};
public:
    virtual void MyPrint(){
        cout << "a=" << a_ << ",b=" << b_ << endl;
    }
};

//类中静态成员不算在实例大小内，存放在数据段中
class CaseC {
    int a_{12};
    int b_{21};
    static int c_;
};
int CaseC::c_=33;
#endif

// g++ -fdump-class-hierarchy main.cpp 
//

int main()
{

#if 0
    //case A
    CaseA caseA;
    char* p = (char*)&caseA;
    cout << *(int*)p << " " << (int*)p << endl; // 12
    cout << *(int*)(p+4) << " " << (int*)(p+4) << endl; // 21
    /*
    linux输出:
    12 0x7ffc087f30b0
    21 0x7ffc087f30b4

    从输出结果来看,顺序存储，地址从低到高
    */
#endif

#if 0
   //case B
    CaseB caseB;
    char *p = (char *)&caseB;
    typedef void (*vfuncType)(CaseB*);
    vfuncType vfunc;
    cout << sizeof(vfunc) << endl;
    cout << "sizeof(int*)="<< sizeof(int*) << endl;
    cout << *(int *)(p + 8) << endl;     //a_
    cout << *(int *)(p + 8 + 4) << endl; //b_

    caseB.MyPrint();
    //直接通过指针偏移方法调用虚拟函数
    // int *vptr = (int*)(*(long*)&caseB);
    CaseB* pB = &caseB;
    long *vptr = (long *)(*(long *)pB);
    cout << "virtual table address = " << vptr << endl; //cout << &"HelloWorld!" << endl; 和这个输出的值相近 说明在常量区
    
    static int n = 100;
    cout << "static int n address  = " << &n << endl; // > cout << &"HelloWorld!" << endl;
    cout << "字面量HelloWorld 地址  = " << &"HelloWorld!" << endl; // 字面量常量区
    cout << "类实例地址 &caseB =" << pB << endl;
    vfunc = (vfuncType)(*vptr);
    vfunc(&caseB); //能正确调用到


#endif

    //虚拟结构内存布局
    // Point2D p2d;
    // cout << "sizeof(Point2D)=" << sizeof(p2d) << endl;
    // printf()
    // long* vbp = (long*)&p2d;
    // cout << "offset=" << *vbp << endl;
    // cout << "x_ = " << *(int*)(*vbp) << endl;
    // cout << "y_ = " << *(int*)(vbp+1) << endl;
    // cout << "x_ = " << *(int*)((int*)vbp + 3) << endl;
    // cout << "" << ((int *)vbp + 3) << endl;

    // printf("ZooAnimal=%d\n", sizeof(ZooAnimal));
    // ZooAnimal za;
    // typedef void (*vfunctype)(ZooAnimal*);
    // vfunctype vfunc;

    // long *vptr = (long*)(*(long *)&za);
    // printf("vptr=%p, vptr+1=%p\n", vptr, vptr+1);
    // vfunc = (vfunctype)(*(vptr + 2)); // ZooAnimal::rotate
    // vfunc(&za);

    TestX();

    return 0;
}