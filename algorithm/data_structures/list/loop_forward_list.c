#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 单向循环链表的实现
 * 第一个节点不保持数据用于判断
 *
*/

typedef int KEY_VALUE;

typedef struct listnode {
    KEY_VALUE        data;
    struct listnode* next;
}NODE,*PNODE;

PNODE create_node(KEY_VALUE data) {
    PNODE new_node = (PNODE)calloc(1, sizeof(NODE));
    assert(new_node != NULL);
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

typedef struct taglist {
    PNODE head;
}LIST, *PLIST;

void init_list(PLIST pl) {
    KEY_VALUE d = 0;
    PNODE first = create_node(d);

}



int main() {
    return 0;
}