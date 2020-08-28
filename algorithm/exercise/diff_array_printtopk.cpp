#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time


/*
 * 有N个长度不一样的数组，所有数组中的元素都是从小到大有序排列的，请从大到小打印这N个数组整体的前K个数
 * 解题思路
 * 构建个大根堆 元素N ，一个数组一个元素，根据数组中最大的元素排序
 * 不断的弹出根，重新调整大根堆，直到弹出要求的个数
 * */

using namespace std;

struct HeapNode{
    int value;
    int arrNum;
    int index;
    //HeapNode(int val, int an, int idx):value(val),arrNum(an),index(idx){}
    void Init(int val, int an, int idx){
        value = val;
        arrNum = an;
        index = idx;
    }
};

struct ArrayOne{
    int  size;
    int* p;
    ArrayOne():p(nullptr),size(0){}
    void Init(int* parr, int sz){
        p = parr;
        size = sz;
    }
};

#define MATRIX_ROWS 10
#define MATRIX_COLS 10

void Show(ArrayOne* pMatrix, int size){
    for (int i = 0; i < size; ++i){
        cout << "index=" << i << "    ";
        for (int j = 0; j < pMatrix[i].size; ++j){
            cout << pMatrix[i].p[j] << " ";
        }
        cout << endl;
    }
}

void swap(HeapNode* heap, int idx1, int idx2){
    HeapNode tmp = heap[idx1];
    heap[idx1] = heap[idx2];
    heap[idx2] = tmp;
}

//trick up
void HeapInsert(HeapNode* heap, int index){
    while (index != 0){
        int parent = (index - 1) / 2;
        if (heap[index].value > heap[parent].value){
            swap(heap, parent, index);
            index = parent;
        } else {
            break;
        }
    }
}


void Heapify(HeapNode* heap, int index, int heapSize){
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int largest = index;
    while (left < heapSize){
        if (heap[left].value > heap[index].value){
            largest = left;
        }
        if (right < heapSize && heap[right].value > heap[left].value){
            largest = right;
        }
        if (largest != index){
            swap(heap, largest, index);
        } else {
            break;
        }

        index = largest;
        left = index * 2 + 1;
        right = index * 2 + 2;
    }
}

void PrintTopK(ArrayOne* pMatrix, int size, int k){
    HeapNode* heap = new HeapNode[size];
    for (int i = 0; i < size; ++i){
        int index = pMatrix[i].size - 1;
        heap[i].value = pMatrix[i].p[index];
        heap[i].arrNum= i;
        heap[i].index = index;
        HeapInsert(heap, i);
    }
    cout << "initialize heap " << " "; 
    for (int i = 0; i < size; ++i){
        cout << heap[i].value << " ";
    }
    cout << endl;

    //cout << heap[0].value << endl;
    cout << "TOP " << k << " : " ;
    int heapSize = size;
    for (int i=0; i < k; ++i){
        if (heapSize == 0) break;
        cout << heap[0].value << " ";
        if (heap[0].index >= 0){
            heap[0].index --;
            heap[0].value = pMatrix[heap[0].arrNum].p[heap[0].index];
        } else {
            swap(heap, 0, --heapSize);
        }
        Heapify(heap, 0, heapSize);
        //Show(pMatrix, heapSize);

    }
    cout << endl;



    delete[] heap;
}

inline int SafeRangeRand(int lowerbound, int upperbound) {
    if(lowerbound <= upperbound ){
        return  lowerbound + (int)((upperbound - lowerbound + 1) * (rand() / (RAND_MAX + 1.0)));    
    }
    return  upperbound + (int)((lowerbound - upperbound + 1) * (rand() / (RAND_MAX + 1.0)));
}

int main(){
    srand(time(0));

    ArrayOne matrix[MATRIX_ROWS];
    for (int i = 0; i < MATRIX_COLS; ++i){
        int sz = i + 1;
        int* pi = new int[sz];
        for (int j = 0; j < sz; ++j){
            //pi[j] = rand() % 100000 + 1;
            int lowBound = j*10;
            int upBound = (j+1)*10;
            pi[j] = SafeRangeRand(lowBound, upBound);
        }

        matrix[i].Init(pi, sz);
    }
    Show(matrix, MATRIX_ROWS);
    PrintTopK(matrix, MATRIX_ROWS, 5);



    //delete
    for (int i = 0; i < MATRIX_COLS; ++i){
        delete[] matrix[i].p;
        matrix[i].p = nullptr;
        matrix[i].size = 0;
    }

    return 0;
}
