#ifndef AL_QUEUE_CPP_H
#define AL_QUEUE_CPP_H

namespace al {

/* 顺序存储队列的简单实现
 * 第一个元素位置留空，没有存储数据，方便编写代码
 */

template<typename T>
class Queue {
public:
    Queue(int capacity=10);
    bool IsEmpty();
    T& Front();
    void Enqueue(const T& e);
    void Dequeue();
    int  Capacity();
private:
    T* queue;
    int front;
    int rear;
    int capacity;
};

template<typename T>
inline Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
    if (capacity < 1) capacity = 2;
    queue = new T[capacity];
    front = rear = 0;
}

template<typename T>
inline bool Queue<T>::IsEmpty()
{
    return front == rear;
}

template<typename T>
inline T& Queue<T>::Front()
{
    if (IsEmpty()) {
        throw "Queue is empty.";
    }
        
    return queue[(front + 1) % capacity];
}

template<typename T>
inline void Queue<T>::Enqueue(const T& e)
{
    if ((rear + 1) % capacity == front) {
        T* newQueue = new T[2 * capacity];

        int start = (front + 1) % capacity;
        if (start < 2) {
            std::copy(queue + start, queue + start + capacity - 1, newQueue);
        }
        else {
            std::copy(queue + start, queue + capacity, newQueue);
            std::copy(queue, queue + rear + 1, newQueue + capacity - start);
        }
        front = 2 * capacity - 1;//下一个访问的是newQueue的第一个元素
        rear = capacity - 2;
        capacity *= 2;
        delete[] queue;
        queue = newQueue;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = e;
}

template<typename T>
inline void Queue<T>::Dequeue()
{
    if (IsEmpty()) {
        throw "Queue is empty.";
    }
    front = (front + 1) % capacity;
    queue[front].~T();
}

template<typename T>
inline int Queue<T>::Capacity()
{
    return capacity;
}

}

#endif // !AL_QUEUE_CPP_H