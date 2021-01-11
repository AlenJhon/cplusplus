#include <iostream>
#include <deque>

/*
给定一个整型数组arr和整数w，表示一个大小为w的窗口从数组的最左边滑到最右边。
求每次窗口内的最大值，并返回结果数组
举例
arr=[4, 3, 5, 4, 3, 3, 6, 7] , w= 3 时，最终返回[5, 5, 5, 4, 6, 7]
[4, 3, 5], 4, 3, 3, 6, 7        窗口中最大值为5
4, [3, 5, 4], 3, 3, 6, 7        窗口中最大值为5
4, 3, [5, 4, 3], 3, 6, 7        窗口中最大值为5
4, 3, 5, [4, 3, 3], 6, 7        窗口中最大值为4
4, 3, 5, 4, [3, 3, 6], 7        窗口中最大值为6
4, 3, 5, 4, 3, [3, 6, 7]        窗口中最大值为7
*/

using namespace std;

void GetMaxWindow(int* arr, int sz, int w) {
    if (arr == nullptr || w < 1 || sz < w) {
        return ;
    }

    deque<int> dq;

    int len = sz - w + 1;
    int* res = new int[len];

    int rescnt = 0;
    for (int i = 0; i < sz; ++i) {
        
        //从尾往前看如果发现<=当前新加入窗口的值从队列pop_back
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);//当前节点的下标加入队列

        //查看队首是否过期
        if (dq.front() == i - w) {
            dq.pop_front();
        }
        //结果保持
        if (i >= w - 1) { //窗口没形成不收集数
            res[rescnt++] = arr[dq.front()];
        }
    }


    for (int i = 0; i < len; ++i) {
        cout << res[i] << " ";
    }
    cout << endl;
    delete[] res;
}

int main() {
    int arr[] = {4, 3, 5, 4, 3, 3, 6, 7};
    int len = sizeof(arr) / sizeof(int);
    GetMaxWindow(arr, len, 3);

    return 0;
}
