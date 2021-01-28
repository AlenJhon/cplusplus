#include <iostream>
#include <vector>
using namespace std;
/**
 * 一段时间会实现一次,因为我经常往老是记不住
*/

void InsertSort(vector<int>& vi){
    for(int i=1; i<vi.size(); ++i){
        int cur = vi[i];
        // int j;
        // for(j=i-1; j>=0; --j){
        //     if (cur < vi[j]){
        //         vi[j+1] = vi[j];
        //     } else {
        //         break;
        //     }
        // }
        int j = i -1;
        while(j>=0 && cur < vi[j]){
            vi[j+1] = vi[j];
            --j;
        }

        if(i != (j+1)){
            vi[j+1] = cur;
        }
    }
    return;
}


int main(){
    vector<int> vi{4, 3, 5, 9, 10, 1, 2, 8, 7};
    InsertSort(vi);

    for(const auto& it: vi){
        cout << it << " ";
    }
    cout << endl;
    return 0;
}