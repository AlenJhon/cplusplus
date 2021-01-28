#include <iostream>
#include <vector>

using namespace std;

/**
 * 编码时间2021-01-15
*/

void SelectSort(vector<int>& vi){
    for(int i=0; i<vi.size(); ++i){
        int min = i;
        for(int j=i+1; j<vi.size(); ++j){
            if (vi[j] < vi[min]){
                min = j;
            }
        }
        if(i != min){
            int t = vi[i];
            vi[i] = vi[min];
            vi[min] = t;
        }
    }
}

int main(){
    vector<int> vi{10,5,4,6,3,2,1,9,8,7};
    SelectSort(vi);

    for(const auto& it : vi){
        cout << it << " ";
    }
    cout << endl;

    return 0;
}