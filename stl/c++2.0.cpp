
/************************************************************************/
/* Variadic Templates                                                   */
/* 数量不定的模板参数                                                      */
/************************************************************************/
#include <iostream>
using namespace std;

void vtprint() {}


template<typename... Types>
void vtprint(const Types&... args) {
    cout << "vtprint(const Types&... args)" << endl;
    vtprint(args...);
}

template<typename T, typename... Types>
void vtprint(const T& first_arg, const Types&... args) {
    cout << first_arg << endl;
    vtprint(args...);
}




int main(int argc, char** argv) {
    vtprint(1, 7.5, "HelloWorld.", 'a');

    return 0;
}