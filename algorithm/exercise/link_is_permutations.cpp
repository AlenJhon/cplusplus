#include <iostream>
#include <stack>
//#include <forward_list>

/*
判断一个链表是回文结构
1 -> 2 -> 3 -> 4 -> 3 -> 2 -> 1

方法1：遍历链表依次将数据压入栈中，全部压完后，数据一个个出栈和链表对比，如果多对的上就是回文结构
方法2：用快慢指针求出链表中间位置，将中间位置后半部分的数据依次入栈，出栈时和链表头部开始一个个对比，如果栈中出来的数据都能比对的上，说明是回文结构
方法3：用快慢指针求出链表中间位置，将链表的后半部分逆序，两头比对，如果直到中间都是一样的，说明是回文结构，如果中间出现不一致的说明不是

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
    //方法2
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

    //不支持快慢指针遍历
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