#include <iostream>
#include <stack>

using namespace std;

/**
 * 目标是实现栈的反转
 * 主要是考察对递归，系统调用栈的了解
 * 
*/

//获取栈底
//利用系统调用栈的特点，将stack中的内容一个个pop出来缓存在系统栈中，将最后一个元素（栈底）层层返回
int GetStackBase(stack<int>& si){
    int cur = si.top();
    si.pop();
    if(si.empty()){
        return cur;
    }

    int res = GetStackBase(si);
    si.push(cur);
    return res;
}

void ReverseStack(stack<int>& si){
    int base = GetStackBase(si);
    if(si.empty()){
        si.push(base);
        return;
    }
    ReverseStack(si);
    si.push(base);
    return;
}


int main(){
    stack<int> si;
    for(const auto& it: {1,2,3,4}){
        si.push(it);
    }
    // while(!si.empty()){
    //     cout << si.top() << endl;
    //     si.pop();
    // }
    // cout << GetStackBase(si) << endl;
    ReverseStack(si);

    while(!si.empty()){
        cout << si.top() << endl;
        si.pop();
    }

    return 0;
}