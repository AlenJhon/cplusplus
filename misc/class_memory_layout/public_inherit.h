#include <cstdio>
class ZooAnimal{
public:
    ZooAnimal():loc(1),loc2(2){}
    virtual ~ZooAnimal(){
        printf(" ~ZooAnimal\n");
    }
    virtual void rotate(){
        printf("ZooAnimal::rotate\n");
    }
private:
    int loc;
    int loc2;
};


class Bear : public ZooAnimal {
public:
    void rotate(){
        printf("Bear::rotate\n");
    }

private:
    int bear;
};