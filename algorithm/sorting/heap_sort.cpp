#include <iostream>
//#include "data_structures/heap/max_heap_cpp.h"   //使用写好的堆进行排序

using namespace std;


//build cmd   g++ heap_sort.cpp -I ..
//利用大根堆进行排序
//时间复杂度O(nlogn)

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//检查 节点是否需要下沉
void make_max_heap(int* arr, int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1]) {
            son++;
        }
        if (arr[dad] > arr[son]) {
            return;
        } else {
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void TrickleDown(int* arr, int idx, int end) {

    if (idx > end) {
        return;
    }
    int son = 2 * idx + 1;
    if (son > end) {
        return;
    }

    if (son + 1 <= end && arr[son] < arr[son + 1]) {
        son += 1;
    }
    if (arr[idx] < arr[son]) { //大根堆小的下沉
        swap(arr + idx, arr + son);
    }

    TrickleDown(arr, 2 * idx + 1, end);
    TrickleDown(arr, 2 * idx + 2, end);
}

void heap_sort(int* arr, int len) {
    int i;
    //生成一个大根堆，从最后的一个父节点开始查看下沉，不停的查看向下渗透
    for (i = len / 2 - 1; i >= 0; --i) {
        //make_max_heap(arr, i, len - 1);  
        TrickleDown(arr, i, len - 1);
    }
    

    //不停的从堆中取出最大的元素，
    for (i = len - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]);
        //make_max_heap(arr, 0, i - 1);
        TrickleDown(arr, 0, i-1);
    }
}



int main() {

    int arr[] = { 14, 73, 42, 16, 0, 9, 4, 11, 65, 33, 20, -90, 455, 988,520,776 };
    int len = sizeof(arr) / sizeof(int);

#if 0
    for (int i = 0; i < len; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    al::MaxHeap<int> h(len+1);
    for (int i = 0; i < len; ++i) {
        h.Push(arr[i]);
    }   
    h.Show(0);

    //从大根堆中一个个取出写入数据等同于从大到小排序
    for (int i = 0; i < len; ++i) {
        arr[i] = h.Top();
        h.Pop();
    }
#endif
    heap_sort(arr, len);


    for (int i = 0; i < len; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;



    return 0;
}