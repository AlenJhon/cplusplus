#include <iostream>

using namespace std;

#define SHORT_SIZEOF(x) \
    cout << "sizeof("#x")=" << sizeof(x) << endl

#include <typeinfo> //for typeid
#include <cxxabi.h> // for __cxa_demangle
#include <cstddef> // for nullptr
template<typename Type>
void show_sizeof() {
    // cout << "sizeof(" << typeid(Type).name() << ")=" << sizeof(Type) << endl;

    char *name = abi::__cxa_demangle(typeid(Type).name(), nullptr, nullptr, nullptr);
    cout << "sizeof(" << name << ")=" << sizeof(Type) << endl;
}    

int main() {

    // cout << "sizeof(short)=" << sizeof(short) << endl;
    // cout << "sizeof(int)=" << sizeof(int) << endl;
    // cout << "sizeof(long)" << sizeof(long) << endl;
    // cout << "sizeof(long long)=" << sizeof(long long) << endl;
    // cout << "sizeof(unsigned long long)=" << sizeof(unsigned long long) << endl;

    // SHORT_SIZEOF(short);
    // SHORT_SIZEOF(int);
    // SHORT_SIZEOF(long);
    // SHORT_SIZEOF(long long);
    // SHORT_SIZEOF(unsigned long long);

    show_sizeof<short>();
    show_sizeof<int>();
    show_sizeof<long>();
    show_sizeof<long long>();
    show_sizeof<unsigned long long>();

    return 0;
}