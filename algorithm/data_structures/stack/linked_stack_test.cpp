#include "linked_stack_cpp.h"
#include <iostream>

using namespace std;

int main() {
    cout << "start test LinkedStack ..." << endl;
    al::LinkedStack<int> s;

    if (s.IsEmpty() == false) {
        cout << "test IsEmpty failed ..." << endl;
    }

    s.Push(11);
    if (s.Top() != 11) {
        cout << "test Top failed ..." << endl;
    }

    s.Push(12);
    if (s.Top() != 12) {
        cout << "test Top failed ..." << endl;
    }
    s.Push(13);
    s.Push(14);
    s.Pop();
    if (s.Top() != 13) {
        cout << "test Top failed ..." << endl;
    }

    cout << s.IsEmpty() << endl;
    s.Clear();
    if (s.IsEmpty() == false) {
        cout << "test IsEmpty failed ..." << endl;
    }
    cout << "test LinkedStack success ..." << endl;

    return 0;
}