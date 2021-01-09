#include <iostream>

using namespace std;

class Demo {
    int *num_;
public:
    Demo():num_(new int(0)){
        cout << "construct!" << endl;
    }

    ~Demo(){
        cout << "class destruct!" << endl;
    }

    Demo(const Demo& d):num_(new int(*d.num_)) {
        cout << "copy construct!" << endl;
    }

    //move construct
    Demo(Demo && d):num_(d.num_){
        d.num_ = nullptr;
        cout << "move construct!" << endl;
    }
};

Demo GetDemo() {
    return Demo();
}

//g++ move_construct.cpp -fno-elide-constructors

int main() {

    Demo a = GetDemo();

    return 0;
}

/**
 * 编译指令
 * g++ move_construct.cpp -fno-elide-constructors
 * 
 * 没有移动构造函数的情况
 * construct!
copy construct!
class destruct!
copy construct!
class destruct!
class destruct!
 *   
 * 添加移动构造函数之后输出结果
 * construct!
move construct!
class destruct!
move construct!
class destruct!
class destruct!
*/