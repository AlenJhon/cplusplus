#include <iostream>
#include "stack_cpp.h"


using namespace std;

int main() {
    al::Stack<int> s(5);

    cout << s.IsEmpty() << endl;
    s.Push(10);
    cout << s.IsEmpty() << endl;
    for (int i = 2; i <= 6; ++i) {
        s.Push(i * 10);
    }
    cout << s.Capacity() << endl;
    cout << s.Top() << endl;
    s.Pop();
    cout << s.Top() << endl;

    return 0;
}