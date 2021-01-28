#include <iostream>
#include <vector>
using namespace std;

/**
 * 编写时间2021-01-15 ,每段时间会写一遍
*/
void BubbleSort(vector<int>& vi){
    for(int i=vi.size()-1; i>=0; --i){
        for(int j=0; j<i; ++j){
            if(vi[j] > vi[j+1]){
                int t = vi[j];
                vi[j] = vi[j+1];
                vi[j+1] = t;
            }
        }
    }
    return;
}

int main(){
    vector<int> vi{10,5,4,6,3,2,1,9,8,7};
    BubbleSort(vi);

    for(const auto& it: vi){
        cout << it << " ";
    }
    cout << endl;

    return 0;
}