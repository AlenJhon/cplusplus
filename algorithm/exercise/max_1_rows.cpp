#include <iostream>
#include <stack>

/*
 * 给定一个二位数组，数组中只有0,1两种数，1一定在0的右边
 * 传入这样的一个数组输出，最多个 1的行索引，如果有多行一样的都依次输出
 *
 * */

using namespace std;



void Max1Rows(int arr[][10], int len, int hei){
    int max = 0;
    stack<int> s;

    int j = len - 1;
    for (int i = 0; i < hei; ++i){
        int rowc = 0;

        for (; j >= 0; --j){
            if (arr[i][j] == 1)	{
                rowc += 1;
            } else {
                --j;
                break;
            }
        }
        j += 1;

        if (arr[i][j] == 0){
            continue;
        } else {
            rowc = len - j;		
        }

        if (max < rowc){
            while (!s.empty()){
                s.pop();
            }
            s.push(i);
            max = rowc;
        } else if (max == rowc){
            s.push(i);
        }
    }

    while (!s.empty()){
        cout << s.top() << endl;
        s.pop();
    }
}


int main(){

    int arr[10][10] = {
        1,1,1,1,1,1,1,1,1,1,
        0,0,0,0,1,1,1,1,1,1,
        0,0,0,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        0,0,0,0,0,1,1,1,1,1,
        0,0,0,0,1,1,1,1,1,1,
        0,0,0,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
    };
    Max1Rows(arr, 10, 10);

    return 0;
}
