#ifndef __concrete_observer_h__
#define __concrete_observer_h__

#include <iostream>
#include <string>
#include "observer.h"

using namespace std;

class concrete_observer : public iobserver {
private:
    string name_;

public:
    concrete_observer(string name):name_(name) {}

    void update(double price) {
        // cout << price << endl;
        cout << name_ << " - price : " << fixed  <<  price << endl;
        // cout << name_ << " - price : " ;
        // cout.precision(5);
        // cout << price << endl;
    }
};

#endif // __concrete_observer_h__