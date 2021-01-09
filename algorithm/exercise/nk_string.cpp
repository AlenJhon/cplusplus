#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
这是一个华为机考题，自己动手做了一遍，但是花的时间超出了预期，主要还是很多输入输出方法不熟悉，还有对牛客网的做题也不了解
比如牛客网中需要支持多组数据的输入是需要，类似以下的方式
int main() {
    //getlines(cin, str)
    while(cin >> num) {
        ...
    }
}
*/
struct ElementOne {
    string key;
    int num{0};
};

int main() {
    string path;
    int rowNum = 0;
    vector<ElementOne> l;
    l.reserve(1024);//事先预留空间，要是对内存没要求可以预留多点，可能可以提高性能

    //获取输入依次加入到vector中
    while (cin >> path) {
        cin >> rowNum;
        size_t pos = path.find_last_of("\\");
        string key;
        if (pos) {
            key = path.substr(pos+1);
        } else {
            key = path;
        }
        key = key+" "+to_string(rowNum);//文件和行号组在一起当成key

        //
        l.push_back({key, 1});
    }
    //
    vector<ElementOne> l2;
    l2.reserve(1024);

    //遍历数组将相同key的合并放入新的vector
    for (auto& it: l) {
        if (it.num < 1) {
            break;
        }
        // cout << it.key << endl;
        bool is_find = false;
        for (auto& it2: l2){
            if (it2.key == it.key) {
                it2.num += 1;
                is_find = true;
            }
        }
        if (!is_find) {
            l2.push_back({it.key, 1});
        }
    }
 

    //order
    //使用稳定的排序算法（插入排序）
    //题目指定前8个可以只选定最大的8个就跳出循环，提高效率
    for (int i = 1; i < l2.size(); ++i) {
        if (l2[i].num < 1) {
            break;
        }
        int tmp = i;
        for (int j = i-1; j >= 0; --j) {
            if (l2[i].num > l2[j].num) {
                ElementOne t = l2[j];
                l2[j] = l2[i];
                l2[i] = t;
                i = j;
            }
        }
        if (i == 8) {
            break;
        }
    }


    //print result
    // cout << "xxxxxxx" << endl;
    for (int i=0; i < 8 && i < l2.size(); ++i) {
        if (l2[i].num < 1) {
            break;
        }
        int fileLen = l2[i].key.find_last_of(" ");
        if (fileLen > 16) {
            cout << l2[i].key.substr(fileLen-16, 1024) << " " << l2[i].num << endl;
        } else {
            cout << l2[i].key << " " << l2[i].num << endl;
        }
    }
    return 0;
}

// #include <iostream>
// #include <unordered_map>
// #include <cstring>
// #include <queue>
// #include <string>
// struct stone {
//     int num;
//     string key;
// };

// struct stOneCmp {
//     bool operator()(const stone& a, const stone& b) {
//         return a.num < b.num;
//     }
// };




// int main() {

    // string path;
    // int rowNum = 0;
    // unordered_map<string, int> um;
    // priority_queue<stone, vector<stone>, stOneCmp> q;

    // while (cin >> path) {
    //     cin >> rowNum;
    //     size_t pos = path.find_last_of("\\");
    //     string key;
    //     if (pos) {
    //         key = path.substr(pos+1, 1024);
    //     } else {
    //         key = path;
    //     }
    //     key = key+" "+to_string(rowNum);
    //
    //     const auto& it = um.find(key); //顺序不固定，这种方式行不通
    //     if (it != um.end()) {
    //         it->second += 1;
    //     } else {
    //         um.insert(pair<string, int>(key, 1));
    //     }
    // }

    //目的是想要获取出前8的大小，但是顺序发生了改变
    // for (auto& it : um) {
    //     stone one;
    //     one.num = it.second;
    //     one.key = it.first;
    //     q.push(one);
    // }
    
    //不稳定，顺序发生了改变
    // while(!q.empty()) {
    //     int fileLen = q.top().key.find_last_of(" ");
    //     if (fileLen > 16) {
    //         cout << q.top().key.substr(fileLen-16, 1024) << " " << q.top().num << endl;
    //     } else {
    //         cout << q.top().key << " " << q.top().num << endl;
    //     }
    //     q.pop();
    // }


//     return 0;
// }
