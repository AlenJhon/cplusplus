#ifndef AL_MAX_HEAP_CPP_H
#define AL_MAX_HEAP_CPP_H

namespace al {

template<typename T>
class MaxHeap {
public:
    MaxHeap(int mx = 10);
    ~MaxHeap();

    void Push(const T& e);
    const T& Top();
    void Pop();
    bool IsEmpty();

    void Show(int idx=0);//for test
private:
    void TrickleUp(int idx);
    void TrickleDown(int idx);

    T* root;
    int size;
    int capacity;
};

template<typename T>
void MaxHeap<T>::Show(int idx) {
    if (idx >= size) {
        return;
    }
    Show(2 * idx + 1);
    std::cout << "idx=" << idx << ",value=" << root[idx] << std::endl;
    Show(2 * idx + 2);
}

template<typename T>
MaxHeap<T>::MaxHeap(int mx) :capacity(mx) {
    root = new T[capacity];
    size = 0;
}

template<typename T>
MaxHeap<T>::~MaxHeap() {
    if (root) {
        delete root;
        //root = nullptr
        root = 0;
        size = 0;   
        capacity = 0;
    }
}


template<typename T>
void MaxHeap<T>::Push(const T& e) {
    if (size >= capacity) {
        throw "MaxHeap Full .";//在这里没有进行扩大处理只是学习堆结构
    }
    root[size] = e;
    size += 1;
    TrickleUp(size-1);
}

template<typename T>
const T& MaxHeap<T>::Top() {
    if (IsEmpty()) {
        throw "heap is empty.";
    }
    return root[0];
}

template<typename T>
void MaxHeap<T>::Pop() {
    if (IsEmpty()) {
        return;
    }

    root[0] = root[size];
    size -= 1;
    TrickleDown(0);
}

template<typename T>
bool MaxHeap<T>::IsEmpty() {
    return size == 0;
}

template<typename T>
void MaxHeap<T>::TrickleUp(int idx) {
    T tmp = root[idx];

    int pos = idx;
    int parent = (pos - 1) / 2;
    while (pos > 0 && tmp > root[parent]) {
        root[pos] = root[parent];
        pos = parent;
        parent = (parent - 1) / 2;
    }
    root[pos] = tmp;
}

template<typename T>
void MaxHeap<T>::TrickleDown(int idx) {
    T tmp = root[idx];

    int pos = idx;
    while (pos < size) {
        int left = 2 * pos + 1;
        int right = 2 * pos + 2;
        if (left < size && tmp < root[left] && root[left] > root[right]) {
            root[pos] = root[left];
            pos = left;
        } else if (right < size && tmp < root[right] && root[right] > root[left]) {
            root[pos] = root[right];
            pos = right;
        } else {
            break;
        }
    }
    root[pos] = tmp;
}


}

#endif //!AL_MAX_HEAP_CPP_H
