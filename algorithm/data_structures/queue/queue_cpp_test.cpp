#include <iostream>
#include "queue_cpp.h"

using namespace std;
int main() {
    al::Queue<int> q(4);

    cout << q.IsEmpty() << endl;
    cout << "Capacity=" << q.Capacity() << endl;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);
    cout << "Capacity=" << q.Capacity() << endl;

    cout << q.Front() << endl;

    while (!q.IsEmpty()) {
        cout << q.Front() << endl;
        q.Dequeue();
    }

    return 0;
}