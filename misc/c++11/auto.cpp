#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

typedef struct row{
    int id;
    string name;
}ROW;

int main(){
    ROW desc[10] {0};
    for (int i=0; i < 10; ++i){
        desc[i]={i+1, "ttname"};
    }
    unordered_map<int, vector<const ROW*>> tone;
    for (int i=100; i<110; ++i){
        tone[i+1].push_back(&desc[i-100]);
    }

    for (auto iter : tone){
        cout << iter.first << endl; // don't iter->first
        for (auto x : iter.second){ // don't iter->second
            cout << x->id << x->name << endl;
        }
    }

    return 0;
}