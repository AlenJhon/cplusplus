#include <iostream>
#include <map>

using namespace std;

int main(){
    map<int, int> tmap;
    tmap[1] = 100;
    tmap[1] = 200; //覆盖 100

    typedef map<int, int>::iterator iter;
    pair<iter, bool> ret = tmap.insert(make_pair(1, 300)); // 插入失败 并没有修改容器
    if (ret.second == false){
        cout << "insert 1 300 failed." << endl;
    }

    cout << tmap[1] << endl;
    cout  << tmap.size() << endl;

    //现在数中只有一个元素 1:200
    tmap.erase(1);
    cout << tmap.size() << endl;

    return 0;
}
