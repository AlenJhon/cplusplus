/**
 * 给定一个字符串abc,列出该字符串的所有子字符串,abc,a,ab,ac,b,bc,c
 * 这个可以用二叉树虚拟出来,头脑里的一个结构,两个分叉一个选择,一个不选择,组合出的一个串
 * 
*/
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

void substr(string& s, int idx, unordered_set<string>& ans, string& path){
    if (s.size() == idx){
        if (path != ""){
            ans.insert(path);
        }
        return;
    }
    string no = path;
    substr(s, idx+1, ans, no);
    string yes = path + s[idx];
    substr(s, idx+1, ans, yes);
}

int main(){
    string str = "abc";
    unordered_set<string> ans;
    string path = "";
    substr(str, 0, ans, path);
    for( auto& k : ans){
        cout << k << endl;
        // printf("%s\n", k.c_str());
    }

    return 0;
}