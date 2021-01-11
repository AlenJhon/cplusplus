/*
这个题目是
有一个数组a[N]顺序存放0~N-1，要求每隔两个数删掉一个数，到末尾时循环至开头继续进行，求最后一个被删掉的数的原始下标位置。以8个数(N=7)为例:｛0，1，2，3，4，5，6，7｝，0->1->2(删除)->3->4->5(删除)->6->7->0(删除),如此循环直到最后一个数被删除。
输入描述:
每组数据为一行一个整数n(小于等于1000)，为数组成员数,如果大于1000，则对a[999]进行计算。

输出描述:
一行输出最后一个被删掉的数的原始下标位置。

输入例子1:
8

输出例子1:
6
*/
// #include <iostream>
// using namespace std;

// int main(){
//     int n = 0;
//     int pos = 2;
//     while (cin >> n) {
//         if (n > 1000) {
//             n = 1000;
//         }
//         pos = -1;
//         int count = n;
//         int gap = 3;
//         while(count--) {
//             if (count == 0) {
//                 cout << "res " << (pos+gap-1)%n << endl;
//                 break;
//             }     
//             pos += gap;
//             // if (pos >= n) {
//             //     gap += 1;
//             // }
//             pos %= n;
//             // cout << pos << " " << gap << endl;
//         }
//     }
//     return 0;
// }


/*

*/

#include <iostream>
using namespace std;
int main(){
    int N;
    while(cin >> N){
        int last = 0;
        for(int i = 2;i <= N; ++i)
            last = (last + 3) % i;
        cout << last << endl;   
    }
    return 0;
}
