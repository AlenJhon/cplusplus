#ifndef AL_FORWARD_LIST_H
#define AL_FORWARD_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int KEY_VALUE;
typedef struct _node {
    KEY_VALUE     data;
    struct _node* next;
}LIST_NODE, *PLIST_NODE;

typedef struct {
    PLIST_NODE head;
    int        size;
}LIST, *PLIST;


//prototype
void init_list(PLIST list);//初始化链表
void destory_list(PLIST list);//销毁链表
int size_list(PLIST list);//获取链表元素个数
bool empty_list(PLIST list);//是否为空链表
void insert_head_list(PLIST list, KEY_VALUE data);//插入头部
void remove_list(PLIST list, KEY_VALUE data);//制定数据删除第一个匹配数据
void insert_pos_list(PLIST list, int pos, KEY_VALUE data);//指定位置前插
void reverse_list(PLIST list);//反转链表
void show_list(PLIST list);//for test

#endif //AL_FORWARD_LIST_H