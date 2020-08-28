#include <iostream>
#include <queue>
/**
 * K代表你一共可以选择的项目数，W代表你的初始启动资金，
 * Profits数组代表每个项目的收益，Capital数组代表每个项目需要的启动资金，一个项目能做的条件是你当前的启动资金大于项目的启动资金
 * 一个项目完成后，改项目的收益会加到你的启动资金上，求你能够收获的最大收益。
 * 解题思路：
 * 有个小根堆A存放每个项目的启动资金，有个大根堆B存放当前我资金能做的项目根据收益排序组成的大根堆
 */

using namespace std;

struct IPO {

    struct ProjectOne {
        int capital;
        int profits;
        static void Show(const ProjectOne& a) {
            cout << "capital=" << a.capital << ",profits=" << a.profits << endl;
        }
    };
    struct MyCmp1 {
        bool operator()(const ProjectOne& a, const ProjectOne& b) {
            return a.capital > b.capital;
        }
    };
    struct MyCmp2 {
        bool operator()(const ProjectOne& a, const ProjectOne& b) {
            return a.profits < b.profits;
        }
    };
    priority_queue<ProjectOne, vector<ProjectOne>, MyCmp1> minheap;
    priority_queue<ProjectOne, vector<ProjectOne>, MyCmp2> maxheap;
    ProjectOne* projects;
    int k;
    int w;


    //method
    IPO() {
        k = 10;
        w = 10000;
        projects = new ProjectOne[k];
        for (int i = 0; i < k; ++i) {
            projects[i].capital = 5000 * (i + 1);
            projects[i].profits = 2500 * (i + 1);
        }
    }
    ~IPO() {
        delete[] projects;
    }

    void Work() {
        for (int i = 0; i < k; ++i) {
            minheap.push(projects[i]);
        }

        //ProjectOne::Show(minheap.top());
        for (int i = 0; i < k; ++i) {
            while (!minheap.empty() && minheap.top().capital <= w) {
                //cout << "pop minheap " << endl;
                //ProjectOne::Show(minheap.top());
                maxheap.push(minheap.top());
                minheap.pop();
                //ProjectOne::Show(minheap.top());
            }
            if (maxheap.empty()) {
                cout << "没有项目可以做了" << endl;
                break;
            }

            ProjectOne::Show(maxheap.top());
            w += maxheap.top().profits;
            maxheap.pop();
        }

        cout << "result w=" << w << endl;
    }
};


int main() {
    IPO ipo;
    ipo.Work();

    return 0;
}