#ifndef ABSTRUCT_CLASS_123_
#define ABSTRUCT_CLASS_123_

#include <iostream>

class Company {
public:
    void Recruit() {
        std::cout << "start recruit\n";
        CareerTalk();
        ReceiveResume();
        Interview();
        Offer();
        std::cout << "end recruit\n";
    }
    //宣传会
    void CareerTalk() {
        std::cout << "Career Talk\n";
    }

    //收到简历
    void ReceiveResume() {
        std::cout << "Receive Resume\n";
    }


    virtual void Interview() = 0;
    virtual void Offer() = 0;
};

#endif