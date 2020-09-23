#include <iostream>
#include <stack>
//#include <forward_list>

/*
�ж�һ�������ǻ��Ľṹ
1 -> 2 -> 3 -> 4 -> 3 -> 2 -> 1

����1�������������ν�����ѹ��ջ�У�ȫ��ѹ�������һ������ջ������Աȣ������Ե��Ͼ��ǻ��Ľṹ
����2���ÿ���ָ����������м�λ�ã����м�λ�ú�벿�ֵ�����������ջ����ջʱ������ͷ����ʼһ�����Աȣ����ջ�г��������ݶ��ܱȶԵ��ϣ�˵���ǻ��Ľṹ
����3���ÿ���ָ����������м�λ�ã�������ĺ�벿��������ͷ�ȶԣ����ֱ���м䶼��һ���ģ�˵���ǻ��Ľṹ������м���ֲ�һ�µ�˵������

*/

using namespace std;


typedef struct list_node {
    int data;
    struct list_node* next;
}LIST_NODE, * PLIST_NODE;

typedef struct {
    PLIST_NODE head;
    int        size;
}LIST, * PLIST;

void init_list(PLIST list) {
    // assert(list);
    list->head = NULL;
    list->size = 0;
}

void destory_list(PLIST list) {
    // assert(list);
    PLIST_NODE pos = list->head, next;
    while (pos) {
        next = pos->next;
        free(pos);
        pos = next;
    }
    list->head = NULL;
    list->size = 0;
}

int size_list(PLIST list) {
    return list->size;
}

bool empty_list(PLIST list) {
    return list->size == 0;
}

void insert_head_list(PLIST list, int data) {
    PLIST_NODE new_node = (PLIST_NODE)calloc(1, sizeof(LIST_NODE));
    new_node->data = data;
    new_node->next = list->head;

    list->head = new_node;
    list->size += 1;
}

int main() {
    //����2
    LIST li;
    PLIST plist = &li;
    init_list(plist);
    for (auto x : { 1,2,3,4,3,2,1 }) {
        insert_head_list(PLIST, x);
    }




    //forward_list<int> fl;
    //for (auto x : { 1,2,3,4,3,2,1 }) {
    //    fl.push_front(x);
    //}
    //for (auto it : fl) {
    //    cout << it << " ";
    //}
    //cout << endl;

    //��֧�ֿ���ָ�����
    //forward_list<int>::iterator iter1 = fl.begin();
    //forward_list<int>::iterator iter2 = fl.begin();
    //while (iter2 != fl.end()) {
    //    iter1++;
    //    cout << *iter2 << endl;
    //    iter2++;
    //    if (iter2 == fl.end()) {
    //        break;
    //    }
    //    iter2++;
    //    if (iter2 == fl.end()) {
    //        break;
    //    }
    //}
    //cout << *iter1 << endl;


    return 0;
}