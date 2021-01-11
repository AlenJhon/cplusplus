#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Comp{
    bool operator()(const int& a, const int& b) {
        return a > b;
    }
};

int main() 
{
    unordered_map<int, bool> um;
    priority_queue<int, vector<int>, Comp> q;
    int n = 0;
    int tmp = 0;
    while (cin >> n) {
        while (n--) {
            cin >> tmp;
            um[tmp] = true;
        }
        for(const auto& it : um) {
            q.push(it.first);
        }
        while(!q.empty()) {
            cout << q.top() << endl;
            q.pop();
        }
        um.clear();
    }
    return 0;
}