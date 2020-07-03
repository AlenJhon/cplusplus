#ifndef __subject_h__
#define __subject_h__

class iobserver;

//抽象主题
class isubject {
public:
    virtual void attach(iobserver *) = 0;  //注册观察者
    virtual void detach(iobserver *) = 0;  //注销观察者
    virtual void notify() = 0; // 通知观察者
};

#endif //__subject_h__