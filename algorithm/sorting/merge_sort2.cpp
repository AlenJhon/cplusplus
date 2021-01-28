#include <iostream>
#include <vector>

using namespace std;

/**
 * 编码时间2021-01-15
 * 
 * */

void merge(vector<int>& vi, int ls, int mid, int re){
    vector<int> tmp;
    tmp.reserve(vi.size());

    int i = ls, j = mid+1;
    while(i <= mid && j <= re){
        if(vi[i] <= vi[j]){
            tmp.push_back(vi[i++]);
        }else{
            tmp.push_back(vi[j++]);
        }
    }

    while(i <= mid){
        tmp.push_back(vi[i++]);
    }
    while(j <= re){
        tmp.push_back(vi[j++]);
    }

    i = ls;
    for(const auto& it: tmp){
        vi[i++] = it;
    }
}

void MergeSort_(vector<int>& vi, int left, int right){
    if (left >= right){
        return;
    }
    if(right - left == 1){
        if(vi[left] > vi[right]){
            int t = vi[left];
            vi[left] = vi[right];
            vi[right] = t;
        }
        return;
    }
    int mid = (left + right)/2;
    MergeSort_(vi, left, mid);
    MergeSort_(vi, mid+1, right);
    merge(vi, left, mid, right);
}

void MergeSort(vector<int>& vi){
    MergeSort_(vi, 0, vi.size()-1);
}

int main(){
    // vector<int> vi{1,22,33,44,6,7,8,9,10,11};
    // merge(vi, 0, 3, 9);
    // vector<int> vi{11,22,3};
    // merge(vi,0,1,2);


    vector<int> vi{0,5,4,6,3,2,1,9,8,7};
    // vector<int> vi{0,5,4,6,3,2};
    // vector<int> vi{0,5,4,6,3,2,1};
    MergeSort(vi);

    for(const auto& it: vi){
        cout << it << " ";
    }
    cout << endl;
    return 0;
}