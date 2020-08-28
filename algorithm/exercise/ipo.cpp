#include <iostream>
#include <queue>
/**
 * K������һ������ѡ�����Ŀ����W������ĳ�ʼ�����ʽ�
 * Profits�������ÿ����Ŀ�����棬Capital�������ÿ����Ŀ��Ҫ�������ʽ�һ����Ŀ�������������㵱ǰ�������ʽ������Ŀ�������ʽ�
 * һ����Ŀ��ɺ󣬸���Ŀ�������ӵ���������ʽ��ϣ������ܹ��ջ��������档
 * ����˼·��
 * �и�С����A���ÿ����Ŀ�������ʽ��и������B��ŵ�ǰ���ʽ���������Ŀ��������������ɵĴ����
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
                cout << "û����Ŀ��������" << endl;
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