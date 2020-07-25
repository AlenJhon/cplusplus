#include <iostream>
// #include <stdint.h>
// #include <typeinfo>
// #include <cxxabi.h>

class Fraction {
private:
    int m_numerator;
    int m_denominator;

public:
    Fraction(int num, int den=1)
        :m_numerator(num), m_denominator(den) {}
    operator double() const {
        return  ((double)m_numerator / m_denominator);
    }
};



int main() {

#if 1
    Fraction f(3, 5);
    double d = 4 + f; // 隐式转换  调用operator double()

    std::cout << d << std::endl;
#endif

    // uint32_t dw32 =  100;
    // std::cout << typeid(dw32+1).name() << std::endl;
    // std::cout << abi::__cxa_demangle(typeid(dw32+1).name(),0,0,0 ) << std::endl;

    return 0;
}