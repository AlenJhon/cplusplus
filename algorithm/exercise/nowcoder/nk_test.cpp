#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string findx(vector<string>& vs){
    int max = 0;
    string s;
    for (int i = 0; i < vs.size(); ++i){
        if (max < vs[i].size()){
            max =  vs[i].size();
            s = vs[i];
        }
        if (max != 0 && vs[i].size() == s.size()){
            if (s > vs[i]){
                s = vs[i];
            }
        }
    }
    return s;
}

int main(){
    int idx, num;
    vector<string> vs;
    string tmp;
    while (cin >> idx >> num){
        while (num--){
            cin >> tmp;
            vs.push_back(tmp);
        }
        string res = vs[idx];
        char nextc = res[res.size()-1];
        vector<string> nexts;
        vector<string> exclus;
        exclus.push_back(vs[idx]);

        while (true){
            nexts.clear();
            for (int i = 0; i < vs.size(); ++i){
                if (vs[i][0] == nextc && find(exclus.begin(), exclus.end(), vs[i]) == exclus.end() ){
                    nexts.push_back(vs[i]);
                }
            }
            if (nexts.size() < 1){
                break;
            }
            string ns = findx(nexts);
            nextc = ns[ns.size()-1];
            exclus.push_back(ns);
            res += ns;
        }
        
        cout << res << endl;
    }
    return 0;
}
