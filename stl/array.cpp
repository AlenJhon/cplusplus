#include <array>
#include <ctime>
#include <iostream>
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
    cout << "start test array.\n";

    srand(time(NULL));

    const int n = 1000000;
    array<int, n> a;
    for( int i=0; i < n; ++i) {
        a[i] = rand();
    }

    cout << "array size: " << a.size() << endl;
    cout << "array front :" << a.front() << endl;
    cout << "array back : " << a.back() << endl;

    int target = a[n-1];
    cout << "target : " << target << endl;
    clock_t startTime = clock();
    auto res = find(a.begin(), a.end(), target);//测试结果看优先使用模板方法
    cout << "res:" << *res << ", mili seconds:" << clock() - startTime << endl;


    startTime = clock();
    qsort(a.data(), n, sizeof(int), comp);
    int* res2 = (int*)bsearch(&target, a.data(), n, sizeof(int), comp);
    cout << "res2:" << *res2 << ", mili seconds:" << clock() - startTime << endl;

    /*
    start test array.
array size: 1000000
array front :2128593763
array back : 114396704
target : 114396704
res:114396704, mili seconds:2099
res2:114396704, mili seconds:143540
    */

    return 0;
}


