#ifndef AL_LINDED_QUEUE_H
#define AL_LINDED_QUEUE_H

/* 链式队列的实现
 *
 */

namespace al {

template<typename _TData>
class Queue;

template<typename _TData>
class QueueNode {
    //typedef _TData data_type;

    friend class Queue<_TData>;
private:
    _TData data;
    QueueNode<_TData>* next;

public:
    QueueNode(const _TData& theDt, QueueNode<_TData>* n = 0) :data(theDt),next(n){}
};

template<typename _TData>
class Queue {
    //typedef _TData data_type;
public:
    Queue();
    ~Queue();
public:
    bool IsEmpty();
    _TData& Front();
    void Enqueue(const _TData& e);
    _TData Dequeue();
    void Clear();
private:
    QueueNode<_TData>* front;
    QueueNode<_TData>* back;
};

template<typename _TData>
Queue<_TData>::Queue() {
    front = back = 0;
}

template<typename _TData>
Queue<_TData>::~Queue() {
    Clear();
}

template<typename _TData>
bool Queue<_TData>::IsEmpty() {
    return front == 0;
}

template<typename _TData>
_TData& Queue<_TData>::Front() {
    if (IsEmpty())
        throw "Queue is empty.";
    return front->data;
}

template<typename _TData>
void Queue<_TData>::Enqueue(const _TData& e) {
    if (IsEmpty()) {
        back = front = new QueueNode<_TData>(e);
    }
    else {
        back = back->next = new QueueNode<_TData>(e);
    }
}

template<typename _TData>
_TData Queue<_TData>::Dequeue() {
    _TData frontItem = Front();

    QueueNode<_TData>* old = front;
    front = front->next;
    delete old;

    return frontItem;
}


template<typename _TData>
void Queue<_TData>::Clear() {
    while (!IsEmpty()) {
        Dequeue();
    }
}


}
#endif //!AL_LINDED_QUEUE_H
