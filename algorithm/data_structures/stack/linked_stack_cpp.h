#ifndef LINKED_STACK_H
#define LINKED_STACK_H

namespace al {

template<typename T>
class LinkedStack;

template<typename T>
class ChainNode {
    friend class LinkedStack<T>;
private:
    ChainNode(const T& theData, ChainNode* next = 0) 
        :data(theData), link(next){}

    T data;
    ChainNode<T>* link;
};

template<typename T>
class LinkedStack {
public:
    LinkedStack() :top(0) {}
    ~LinkedStack() { Clear(); }

    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& e);
    void Pop();
    void Clear();
private:
    ChainNode<T>* top;
};

template<typename T>
bool LinkedStack<T>::IsEmpty() const {
    return top == 0;
}

template<typename T>
T& LinkedStack<T>::Top() const {
    if (this->IsEmpty())
        throw "Stack is empty.";
    return top->data;
}

template<typename T>
void LinkedStack<T>::Push(const T& e) {
    top = new ChainNode<T>(e, top);
}

template<typename T>
void LinkedStack<T>::Pop() {
    if (this->IsEmpty())
        throw "Stack is empty. Cannot delete.";
    ChainNode<T>* delNode = top;
    top = top->link;
    delete delNode;
}

template<typename T>
void  LinkedStack<T>::Clear() {
    while (!this->IsEmpty())
        this->Pop();
}

}
#endif // !LINKED_STACK_H
