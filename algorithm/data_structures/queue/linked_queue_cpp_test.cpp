#include <iostream>
#include "linked_queue_cpp.h"

using namespace std;

int main() {
    cout << "Start test linked queue ." << endl;
    al::Queue<int> q;

    cout << q.IsEmpty() << endl;

    cout << "Enqueue data:" << endl;
    for (int i = 1; i < 5; ++i) {
        cout <<  i * 10 << " ";
        q.Enqueue(i * 10);
    }
    cout << endl;

    cout << "Dequeue data:" << endl;
    while (!q.IsEmpty()) {
        cout << q.Dequeue() << " ";
        //q.Dequeue();
    }
    cout << endl;

    cout << q.IsEmpty() << endl;

    return 0;
}