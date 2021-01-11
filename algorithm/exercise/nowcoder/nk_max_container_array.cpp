#include <iostream>
#include <vector>
#include <stack>

using namespace std;


long long maxWater(vector<int>& arr) {
    // write code here
    int n = arr.size();
    //少于等于两个的时候没有容量
    if (n <= 2)
        return 0;
    
    long long res = 0;
    stack<int> high_rec;
    high_rec.push(0);
    
    for (int i = 1; i < n; ++i){
        if (arr[i] <= arr[i-1]){
            if (arr[i] == arr[i-1])
                high_rec.pop();
            high_rec.push(i);//下标入栈
            continue;
        }
        int cur = arr[i-1];
        while (!high_rec.empty()){
            int j = high_rec.top();
            long long a = (i - j - 1), b;
            if (arr[j] <= arr[i]){
                b = (arr[j] - cur);
                res += a * b;
                cur = arr[j];
                high_rec.pop();
            } else {
                b = (arr[i] - cur);
                res += a * b;
                break;
            }
        }
        high_rec.push(i);
    }
    return res;
}

int main() {
    // vector<int> vi = {3,1,2,5,2,4};
    vector<int> vi = {3,1};
    cout << maxWater(vi) << endl;
    return 0;
}
