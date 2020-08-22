#include <iostream>
#include <stack>
#include <unordered_map>
/*
һ�������MaxTree��������
1.�������û���ظ���Ԫ��
2.MaxTree��һ�ö������������ÿһ��ֵ��Ӧһ���������ڵ�
3.����MaxTree�������������е�ÿһ�������ϣ�ֵ���Ľڵ㶼������ͷ

����һ��û���ظ�Ԫ�ص�����arr��д��������������MaxTree�ĺ���
Ҫ���������ĳ���ΪN����ʱ�临�Ӷ�ΪO(N), ����Ŀռ临�Ӷ�ΪO(N)

*/

using namespace std;

struct Node {
    int value;
    Node* left{nullptr};
    Node* right{nullptr};
    Node():left(nullptr),right(nullptr){}
};


void ShowTree(Node* head, int idx) {
    if (!head) {
        //cout << endl;
        return;
    }

    cout << "value= " << head->value << ", idx= " << idx << endl;

    ShowTree(head->left, 2 * idx + 1);
    ShowTree(head->right, 2 * idx + 2);
}

void GetMaxTree(int* arr, int len) {
    Node* pNode = new Node[len];
    for (int i = 0; i < len; ++i) {
        pNode[i].value = arr[i];
    }

    stack<int> s;  //pNode index
    unordered_map<int, Node*> parents;//index -> parent Node*
    for (int i = 0; i < len; ++i) {
        while (!s.empty() && pNode[s.top()].value < pNode[i].value) {
            int lastPopIdx = s.top();
            s.pop();
            parents[lastPopIdx] = (s.empty() || pNode[i].value < pNode[s.top()].value) ? &pNode[i] : &pNode[s.top()];
        }
        s.push(i);
    }
    while (!s.empty()) {
        parents.insert(make_pair(s.top(), s.size() == 1 ? nullptr : &pNode[s.top()]));
        s.pop();
    }

    Node* head = nullptr;
    Node* parent = nullptr;
    for (int i = 0; i < len; ++i) {
        unordered_map<int, Node*>::const_iterator it = parents.find(i);
        if (it == parents.cend()) {
            continue;
        }
        parent = it->second;
        if (parent == nullptr) {
            head = &(pNode[i]);
        } else if (parent->left == nullptr) {
            parent->left = &(pNode[i]);
        } else {
            parent->right = &(pNode[i]);
        }
    }

    //print
    ShowTree(head, 0);

    cout << "Another show ..." << endl;

    for (int i = 0; i < len; ++i) {
        cout << "value=" << pNode[i].value;
        if (pNode[i].left) {
            cout << ",left=" << pNode[i].left->value;
        }
        if (pNode[i].right) {
            cout << ", right=" << pNode[i].right->value;
        }
        cout << endl;
    }

    delete[] pNode;
    return;
}



int main() {
    int arr[] = { 5, 4, 3, 6, 7, 10 };//
    int len = sizeof(arr) / sizeof(int);
    GetMaxTree(arr, len);


    return 0;
}