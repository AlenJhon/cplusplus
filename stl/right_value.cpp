#include <iostream>

using namespace std;

int main(){
    const int && rv = 10;
    // rv = 11;
    const int & lrv = 10;
    //lrv = 11;

    // int && rv = 10;
    // rv = 11;
    return 0;
}