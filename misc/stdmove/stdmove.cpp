//#include <iostream>
/*
 * g++ -S  -o stdmove4.s stdmove.cpp -m32 
 * 生成的汇编代码都是指定32位
 */

#if 0 //case 3
int foo(int && n) {
    int b = 200;
    return n;
}
#endif 


#if 0 // case 5
// #include <iostream> // 习惯用printf
// using namespace std;
#include <stdio.h>

class stack {
private:
    int  *ptr_base_;
    int  top_;
    int  size_;

public:
    stack(int size=100):top_(0),size_(size) {
        // cout << "call stack(int size=)" << endl;   
        printf("call stack(int size=%d) \n", size);   

        ptr_base_ = new int[size];
    }
    
    ~stack() {
        // cout << " ~stack" << endl;
        printf("~stack size_:%d\n",  size_);

        delete [] ptr_base_;
        ptr_base_ = nullptr; // 编译的时候需要加上  -std=c++11
    }
    
    stack(const stack & rsrc):top_(rsrc.top_),size_(rsrc.size_) {
        // cout << "call stack(const stack & rsrc)" << endl;
        printf("call stack(const stack & rsrc) size_:%d\n", rsrc.size_);

        // top_ = rsrc.top_; 放在初始化列表中
        // size_ = rsrc.size_;
        ptr_base_ = new int[rsrc.size_];
        for (int i=0; i < top_; ++i) {
            ptr_base_[i] = rsrc.ptr_base_[i];
        }
        // rsrc.ptr_base_ = nullptr; 不需要你管
    }

    stack& operator =(const stack & rsrc) {
        // cout << "call operator =(const stack & rsrc)" << endl;
        printf("call operator =(const stack & rsrc) size_:%d\n", rsrc.size_);

        if (this == &rsrc)
            return *this;

        delete [] ptr_base_;
        ptr_base_ = new int[rsrc.size_];
        for (int i=0; i < rsrc.top_; ++i) { //记得是拷贝stack中的内容非所有的
            ptr_base_[i] = rsrc.ptr_base_[i];
        }
        top_ = rsrc.top_;
        size_ = rsrc.size_;

        return *this;
    }
};

stack get_stack() {
    stack s2(222);
    return s2;
}
#endif 


#if 1 // case 6
#include <stdio.h>

class stack
{
private:
    int *ptr_base_;
    int top_;
    int size_;

public:
    stack(int size = 100) : top_(0), size_(size)
    {
        printf("call stack(int size=%d) \n", size);

        ptr_base_ = new int[size];
    }

    ~stack()
    {
        printf("~stack size_:%d, %p\n", size_, ptr_base_);

        delete[] ptr_base_;
        ptr_base_ = nullptr; // 编译的时候需要加上  -std=c++11
    }

    stack(const stack &rsrc) : top_(rsrc.top_), size_(rsrc.size_)
    {
        printf("call stack(const stack & rsrc) size_:%d\n", rsrc.size_);

        // top_ = rsrc.top_; 放在初始化列表中
        // size_ = rsrc.size_;
        ptr_base_ = new int[rsrc.size_];
        for (int i = 0; i < top_; ++i)
        {
            ptr_base_[i] = rsrc.ptr_base_[i];
        }
        // rsrc.ptr_base_ = nullptr; 不需要你管
    }

    stack(const stack &&rsrc) : top_(rsrc.top_), size_(rsrc.size_)
    {
        printf("call stack(const stack && src) size_:%d\n", rsrc.size_);
        ptr_base_ = rsrc.ptr_base_;
    }

    stack &operator=(const stack &rsrc)
    {
        printf("call operator =(const stack & rsrc) size_:%d\n", rsrc.size_);

        if (this == &rsrc)
            return *this;

        delete[] ptr_base_;
        ptr_base_ = new int[rsrc.size_];
        for (int i = 0; i < rsrc.top_; ++i)
        { //记得是拷贝stack中的内容非所有的
            ptr_base_[i] = rsrc.ptr_base_[i];
        }
        top_ = rsrc.top_;
        size_ = rsrc.size_;

        return *this;
    }

    stack &operator=(stack &&rsrc) 
    {
        printf("call operator=(const stack && rsrc) size_:%d\n", rsrc.size_);

        if (this == &rsrc)
            return *this;
        
        delete [] ptr_base_;

        ptr_base_ = rsrc.ptr_base_;
        rsrc.ptr_base_ = nullptr; // 需要置空

        top_ = rsrc.top_;
        size_ = rsrc.size_;

        return *this;
    }
};
stack get_stack() {
    stack s2(444);
    return s2;
}
#endif


int main() {

#if 0 // case 1 结果保存在汇编文件 stdmove.s
    int && rref = 100; //将内存中100地址赋值给rref

#elif 0 //case 2 结果保存在汇编文件 stdmove2.s
    int n = 100; // n 中的内存直接写入100

#elif 0 //case 3 结果保存在汇编文件 stdmove3.s
    int rv = foo(100); //右值应用的过程和case 1 是一样的

#elif 0 //case 4 结果保存在汇编文件 stdmove4.s
    const int & crn = 100; // 从汇编的层面来看和 case 1 是一样的

#elif 0 // case 5
    stack s(111);
    s = get_stack();
/* 
* debain 8 64bit 上编译(g++ stdmove.cpp -std=c++11)输出
* call stack(int size=111) 
* call stack(int size=222) 
* call operator =(const stack & rsrc) size_:222
* ~stack size_:222
* ~stack size_:222
* 
* 从结果上看编译器做了优化，也没有在 get_stack构造临时对象返回上一层函数，再用临时对象赋值给s
*/

#elif 1 // case 6
    stack s(333);
    s = get_stack();
/* 
* debain 8 64bit 上编译(g++ stdmove.cpp -std=c++11)输出
* call stack(int size=333) 
* call stack(int size=444) 
* call operator =(const stack && rsrc) size_:444
* ~stack size_:444
* ~stack size_:444
* 
* 从结果上看编译器做了优化，也没有在 get_stack构造临时对象返回上一层函数，再用临时对象赋值给s
*/

#endif
    return 0;
}
