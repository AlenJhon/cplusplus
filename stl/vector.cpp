#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int comp(const void* a, const void* b) {
    if ( *(int*)a > *(int*)b ) {
        return 1;
    } else if (*(int*)a < *(int*)b) {
        return -1;
    }
    return 0;
}


int main() {
    srand(time(nullptr));

    // vector<int> v{1,2,3};// init list
    /*
    vector<int> v;
    const int n = 1000000;
    for (int i = 0; i < n; ++i) {
        v.push_back(rand());
        if (i == 100000) {
            cout << "i=" << i << ",size=" << v.size() << ",capacity=" << v.capacity() << endl;
        }
    }

    cout << "size: " << v.size() << endl;
    cout << "capacity: " << v.capacity() << endl;
    cout << "front: " << v.front() << endl;
    cout << "back: " << v.back() << endl;

    int target = v.back();

    clock_t startTime = clock();
    // auto res = ::find(v.begin(), v.end(), v.back()); // run find time :4973
    // auto res = ::find(v.begin(), v.end(), v.front()); // run find time : 2
    auto res = ::find(v.begin(), v.end(), target);

    cout << "run find time :" << clock() - startTime << endl;
    cout << *res << endl;


    startTime = clock();
    qsort(v.data(), v.size(), sizeof(int), comp);
    cout << "qsort spent mili seconds  :" << clock() - startTime << endl;
    int* res2 = (int*)bsearch(&target, v.data(), v.size(), sizeof(int), comp);
    cout << "res2:" << *res2 << ", mili seconds:" << clock() - startTime << endl;
    */
    /*
i=100000,size=100004,capacity=196608
size: 1000003
capacity: 1572864
front: 1
back: 1807086403
run find time :5175
1807086403
qsort spent mili seconds  :149391
res2:1807086403, mili seconds:149416
    */

    //测试迭代器是否失效
    vector<int> v;
    for (auto i : {1,2,3,4,5}) {
        v.push_back(i);
    }

    //失效了，内部应该是借用迭代器来实现
    for(auto i : v) {
        if (i==2) {
            v.push_back(6);
            v.push_back(7);
            v.push_back(8);
            v.push_back(9);
            v.push_back(10);
        }
        cout << i << " ";
    }
    cout << endl;

    return 0;
}