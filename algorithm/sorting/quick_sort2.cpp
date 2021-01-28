#include <iostream>
#include <vector>

using namespace std;

/**
 * 编码时间2021-01-15
 * 过程
 * 1.取个基点当成是中间点,可以是任选一个,定义两个索引l,r
 * 2.从右边r开始逐一查看如果大于基点,移动一位(--r)继续查看,一旦发现小于基点将这个值存入基点左边l
 * 3.一旦第二步发现小于基点之后,从左边开始逐一遍历查看,如果发现大于基点,将输入写入右边
 * 4.不断的重复2.3,知道l>=r
*/

void QuickSort_(vector<int>& vi, int left, int right){
    int l = left;
    int r = right;
    if(left >= right){
        return;
    }

    int povit = vi[l];
    while(l < r){

        while(l < r && povit <= vi[r]){
            --r;
        }
        vi[l] = vi[r];

        while(l < r && povit >= vi[l]){
            ++l;
        }
        vi[r] = vi[l];
    }
    vi[l] = povit;

    QuickSort_(vi, left, l-1);
    QuickSort_(vi, l+1, right);
    return;
}

void QuickSort(vector<int>& vi){
    QuickSort_(vi, 0, vi.size()-1);
}

int main(){
    vector<int> vi{10,5,4,6,3,2,1,9,8,7};
    QuickSort(vi);

    for(const auto& it: vi){
        cout << it << " ";
    }
    cout << endl;
    return 0;
}