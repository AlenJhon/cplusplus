#ifndef __observer_h__
#define __observer_h__

//抽象观察者
class iobserver {
public:
    virtual void update(double price) = 0; // 更新价格
};

#endif //__observer_h__