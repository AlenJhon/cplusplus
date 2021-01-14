#include <iostream>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> pi(new int(12));
    cout << pi << endl;
    cout << "use_count=" << pi.use_count() << endl;
    cout << "get = " << pi.get() << endl;
    cout << "operator*=" << *pi << endl;

    shared_ptr<int> pi2(pi);
    cout << pi2 << endl;
    cout << "use_count=" << pi2.use_count() << endl;
    cout << "get = " << pi2.get() << endl;
    cout << "operator*=" << *pi2 << endl;

    cout << "use_count=" << pi.use_count() << endl;

    weak_ptr<int> wp(pi);
    cout << "expired=" << wp.expired() << endl;
    cout << "use_count=" << wp.use_count() << endl;
    // cout << "" << wp.owner_before()



    //unique_ptr
    // unique_ptr<int> unipi(new int(33));
    // cout << "get()=" << unipi.get() << endl;
    // // cout << unipi << endl;
    // cout << "operator* = " << *unipi << endl;
    // // cout << " " << unipi.get_deleter() << endl;



    return 0;
}