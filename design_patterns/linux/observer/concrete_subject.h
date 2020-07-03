#ifndef __concrete_subject_h__
#define __concrete_subject_h__

#include <iostream>
#include <list>
#include "subject.h"
#include "observer.h"

using namespace std;

class concrete_subject : public isubject {
private:
    double price_;
    list<iobserver *> observers_;

public:
    concrete_subject():price_(100.0) {}

    void set_price(double price) {
        price_ = price;
    }

    void attach(iobserver *ob) {
        observers_.push_back(ob);
    }

    void detach(iobserver *ob) {
        observers_.remove(ob);
    }

    void notify() {
        list<iobserver *>::iterator it = observers_.begin();
        while (it != observers_.end()) {
            (*it)->update(price_);
            ++it;
        }
    }
};

#endif // __concrete_subject_h__