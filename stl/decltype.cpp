#include <iostream>

using namespace std;

template<typename T, typename U>
auto add(T t, U u) -> decltype(t+u)
{
    return t+u;
}

int main() {
    cout << add(1, 2) << endl;
    cout << add(11.1, 22.2) << endl;
    return 0;
}