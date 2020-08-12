#ifndef STACK_CPP_IMP_H
#define STACK_CPP_IMP_H

namespace al {

template<typename T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize) {
    if (newSize < 0)
        throw "New length must be >= 0.";
    T* newBlock = new T[newSize];
    int minSize = std::min(oldSize, newSize);
    std::copy(a, a + minSize, newBlock);
    delete[] a;
    a = newBlock;
}


template<typename T>
class Stack {
public:
    Stack(int stackCapacity = 10);
    ~Stack();

    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& e);
    void Pop();
    int  Capacity();
    void Clear();
private:
    T* base;
    int top;
    int capacity;
};

template<typename T>
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity) {
    if (capacity < 1)
        throw "stack capacity must be > 0";
    base = new T[capacity];
    top = 0;
}
template<typename T>
Stack<T>::~Stack() {
    if (base)
        delete[] base;
}

template<typename T>
bool Stack<T>::IsEmpty() const {
    return top == 0;
}

template<typename T>
T& Stack<T>::Top() const{
    if (this->IsEmpty())
        throw "stack is empty.";
    return base[top - 1];
}

template<typename T>
void Stack<T>::Push(const T& e) {
    if (top == capacity) {
        ChangeSize1D(base, capacity, 2 * capacity);
        capacity *= 2;
    }
    base[top++] = e;
}


template<typename T>
void Stack<T>::Pop() {
    if (this->IsEmpty()) {
        throw "stack is empty.";
    }
    return base[--top].~T();// destructor
}

template<typename T>
int Stack<T>::Capacity() {
    return capacity;
}

template<typename T>
void Stack<T>::Clear() {
    top = 0;
}


}
#endif // !STACK_CPP_IMP_H

