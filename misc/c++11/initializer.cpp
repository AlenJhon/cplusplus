#include <iostream>


int main() {
    //在gcc 7.5 Ubuntu64 16.04 上编译
    int n {5.0}; //看看编译器是怎么提示从大到小的赋值情况
    //编译器不通过
    /**
     * initializer.cpp:5:15: error: narrowing conversion of ‘5.0e+0’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
    */

    return 0;
}