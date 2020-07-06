//#include <iostream>


int foo(int && n) {
    int b = 200;
    return n;
}

int main() {

#if 0 // case 1
    int && rref = 100;

#elif 0 //case 2
    int n = 100;

#elif 1 //case 3
    int rv = foo(100);

#endif
    return 0;
}
