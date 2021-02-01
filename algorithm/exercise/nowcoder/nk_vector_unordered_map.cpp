/*
输入一个字符串，求出该字符串包含的字符集合

输入描述:
每组数据输入一个字符串，字符串最大长度为100，且只包含字母，不可能为空串，区分大小写。

输出描述:
每组数据一行，按字符串原有的字符顺序，输出字符集合，即重复出现并靠后的字母不输出。

输入例子1:
abcqweracb

输出例子1:
abcqwer
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main(){
    string  str;
    unordered_map<char, bool> um;
    vector<char> vc;
    while( cin >> str ) {
        for (const auto& it : str) {
            if (um.find(it) != um.end()) {
                
            } else {
                um[it] = true;
                vc.push_back(it);
            }
        }
        
        um.clear();
        for(const auto& it : vc) {
            cout << it;
        }
        cout << endl;
        vc.clear();
    }
    return 0;
}