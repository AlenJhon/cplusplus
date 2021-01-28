#include <iostream>
#include <vector>
using namespace std;

//2021-01-15 一段时间会实现一次,练手

bool BinarySearch(vector<int>& vi, int key){
    int left = 0, right = vi.size() - 1;
    while (left <= right){
        int mid = (left+right)/2;
        if (vi[mid] == key){
            return true;
        } else if (vi[mid] < key){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

int main() {
    vector<int> vi{1,2,3,4,5,6,7};
    cout << BinarySearch(vi, 3) << endl;
    cout << BinarySearch(vi, 10) << endl;
    cout << BinarySearch(vi, 1) << endl;
    cout << BinarySearch(vi, 0) << endl;
    return 0;
}