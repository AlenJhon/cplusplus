#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;

int main() {
    map<string, int> msi;
    int i = 100;
    for (auto& it : {"alen", "peter", "lina", "kaka"}){
        // msi[it] = i--;
        msi.insert(pair<string,int>(it, i--));
    }

    for (auto& it : msi) {
        cout << it.first << " : " << it.second << endl;
    }

    // map<int, string> mis;
    // int i = 1;
    // for(auto& it : {"alen", "peter", "lina", "kaka"}){
    //     mis[i] = it;
    //     i += 5;
    // }

    // for (auto& it : mis) {
    //     cout << it.first << " : " << it.second << endl;
    // }


    //set
    // set<string> si;
    // for(auto& it : {"alen", "peter", "lina", "kaka"}){
    //     si.insert(it);
    // }
    // for(const auto& it : si){
    //     cout << it << endl;
    // }

    //unordered_map
    unordered_map<string, int> umsi;
    i = 100;
    for (auto& it : {"alen", "peter", "lina", "kaka"}){
        // umsi[it] = i--;
        umsi.insert(pair<string,int>(it, i--));
    }

    for (auto& it : umsi) {
        cout << it.first << " : " << it.second << endl;
    }
    return 0;
}