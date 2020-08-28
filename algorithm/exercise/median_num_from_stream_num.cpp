#include <iostream>
#include <cstdlib> //qsort ,rand, srand
#include <ctime>
#include <queue>

using namespace std;

struct MyCmp {
    bool operator()(const int& a, const int& b) {
        return a > b;
    }
};

int garr[10];
priority_queue<int, vector<int>, MyCmp> minheap;
priority_queue<int> maxheap;

int StreamNum(int n) {
    minheap.push(n); //����������д��С����

    //�����Ѹ߶Ȳ��1����С���ѵ���һ�����������
    if (minheap.size() > maxheap.size() + 1) {
        int tmp = minheap.top();
        maxheap.push(tmp);
        minheap.pop();
    }
}

int MedainNum() {
    cout << "maxheap.size()=" << maxheap.size() << " ";
    cout << "minheap.size()=" << minheap.size() << endl;
    if (maxheap.size() > minheap.size()) {
        cout << maxheap.top() << endl;
    } else {
        cout << "maxheap.top()=" << maxheap.top() << " ";
        cout << "minheap.top()=" << minheap.top() << " ";
        cout << (maxheap.top() + minheap.top()) / 2 << endl;
    }
}


void Show() {
    for (int i = 0; i < 10; i++) {
        cout << garr[i] << " ";
    }
    cout << endl;
}

int cmp(const void* a, const void* b) {
    if (*(int*)a < *(int*)b) return -1;
    else if (*(int*)a > *(int*)b) return 1;
    return 0;
}

int main() {
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        garr[i] = rand() % 100 + 1;
    }
    Show();

    for (int i = 0; i < 10; i++) {
        StreamNum(garr[i]);
    }
    MedainNum();

    qsort(garr, 10, sizeof(int), cmp);
    Show();

    return 0;
}