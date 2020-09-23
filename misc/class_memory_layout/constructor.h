#include <iostream>
using namespace std;

class X {
public:
    int* pi;
    int z;
    int y;
    int x;
    int p;
};


void TestX() {
    X c;
    cout << "pi=" << c.pi << endl;
    cout << "z=" << c.z << endl;
    cout << "y=" << c.y << endl;
    cout << "x=" << c.x << endl;
    cout << "p=" << c.p << endl;
}