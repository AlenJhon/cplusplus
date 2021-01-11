/*
题目描述
给定一个数组arr，返回子数组的最大累加和
例如，arr = [1, -2, 3, 5, -2, 6, -1]，所有子数组中，[3, 5, -2, 6]可以累加出最大的和12，所以返回12.
[要求]
时间复杂度为O(n)O(n)，空间复杂度为O(1)O(1)

示例1
输入
复制
[1, -2, 3, 5, -2, 6, -1]
返回值
复制
12
*/
#include <iostream>
#include <vector>
using namespace std;

int MaxSumOfSubArray(vector<int>& arr) {
    if (0 == arr.size()) {
        return 0;
    }
    //
    int sum = 0, num = 0;
    for (int i = 0; i < arr.size(); ++i) {
        num = max(arr[i], arr[i]+num);
        sum = max(num, sum);
    }
    return sum;
}

int main()
{
    vector<int> vi{1, -2, 3, 5, -2, 6, -1};
    cout << MaxSumOfSubArray(vi) << endl;
    return 0;
}