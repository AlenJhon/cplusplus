#include <iostream>
#include "max_heap_cpp.h"


using namespace std;

int main() {
    al::MaxHeap<int> h;
    cout << h.IsEmpty() << endl;

    h.Push(10);
    h.Push(25);
    h.Push(50);

    //cout << h.Top() << endl;
    //h.Show(0);

    h.Push(60);
    h.Push(80);
    h.Push(90);
    if (h.Top() != 90) {
        cout << "failed .." << endl;
    }
    h.Show(0);


    h.Pop();
    if (h.Top() != 80) {
        cout << "failed .." << endl;
    }
    h.Pop();
    if (h.Top() != 60) {
        cout << "failed .." << endl;
    }

    cout << "OK" << endl;

    return 0;
}