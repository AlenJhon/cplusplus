#include <iostream>
#include <unordered_map>
#include <string>

/*
给定string类型的数组strArr，再给定整数k，
请严格按照排名顺序打印出次数前k名的字符串
*/
using namespace std;

struct HeapNode {
    string name;
    int count;
    HeapNode(const char* na, int cnt) :name(na), count(cnt) {}
    HeapNode() :count(0) {}
    void Swap(HeapNode* b) {
        string tmpname = name;
        name = b->name;
        b->name = tmpname;

        int tmpcnt = b->count;
        b->count = count;
        count = tmpcnt;
    }
};

//标准中没有栈结构的实现，简单实现个维持指定个数的最小找
struct HeapMin {
    HeapNode* pHead;
    int maxSize;
    int curSize;
    HeapMin(int mx = 10) :maxSize(mx) {
        if (maxSize < 1)
            maxSize = 1;
        curSize = 0;
        pHead = new HeapNode[maxSize];
        if (pHead == nullptr) {
            throw "not any more memory.";
        }

    }
    ~HeapMin() {
        if (pHead) {
            delete[] pHead;
            maxSize = 0;
        }
    }
    void Push(const char* name, int cnt) {
        if (curSize < maxSize) {
            pHead[curSize].name = name;
            pHead[curSize].count = cnt;
            curSize++;

            int i = curSize - 1;
            int j = (i - 1) / 2;
            while (j >= 0 && pHead[i].count < pHead[j].count) {
                pHead[i].Swap(&pHead[j]);
                i = j;
                j = (i - 1) / 2;
            }
            //Show();

        } else {

            if (cnt < pHead[0].count) {
                return;
            }

            pHead[0].name = name;
            pHead[0].count = cnt;

            int i = 0;
            int j = 2 * i + 1;
            while (j < maxSize && pHead[i].count > pHead[j].count) {
                if (j + 1 < maxSize && pHead[j].count < pHead[j + 1].count) {
                    j += 1;
                }
                pHead[i].Swap(&pHead[j]);

                i = j;
                j = 2 * i + 1;
            }
        }
        return;
    }

    void Show() {
        cout << "Show TopK..." << endl;
        cout << "curSize =" << curSize  << ",maxSize=" << maxSize << endl;
        for (int i = 0; i < maxSize; ++i) {
            cout << pHead[i].name << " " << pHead[i].count << endl;
        }
    }
};

void ShowTopK(const char** arr, int len, int k) {
    unordered_map<string, int> nc;
    for (int i = 0; i < len; ++i) {
        nc[arr[i]] += 1;
    }

    //for (auto it : nc) {
    //    cout << it.first << " " << it.second << endl;
    //}

    HeapMin hm(k);

    for (auto it : nc) {
        hm.Push(it.first.data(), it.second);
    }
    hm.Show();
}

int main() {
    const char* pstr1 = "Alen";
    const char* pstr2 = "Peter";
    const char* pstr3 = "Martin";
    const char* pstr4 = "Neo";
    const char* arr[10] = {pstr1, pstr2, pstr3, pstr4, pstr1, pstr1, pstr1, pstr2, pstr2, pstr3 };
    ShowTopK(arr, 10, 2);

    return 0;
}