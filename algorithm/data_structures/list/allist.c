#include "allist.h"



void init_list(PLIST list){
    assert(list);
    list->head = NULL;
    list->size = 0;
}

void destory_list(PLIST list){
    assert(list);
    PLIST_NODE pos = list->head, next;
    while (pos){
        next = pos->next;
        free(pos);
        pos = next;
    }
    list->head = NULL;
    list->size = 0;
}

int size_list(PLIST list){
    return list->size;
}

bool empty_list(PLIST list){
    return list->size == 0;
}

void insert_head_list(PLIST list, KEY_VALUE data){
    PLIST_NODE new_node = (PLIST_NODE)calloc(1, sizeof(LIST_NODE));
    new_node->data = data;
    new_node->next = list->head;

    list->head = new_node;
    list->size += 1;
}

//删除第一个匹配上的元素
void remove_list(PLIST list, KEY_VALUE data){
    PLIST_NODE pos = list->head, prev = NULL;
    if (empty_list(list)){
        printf("empty_list .");
        return;
    }

    while (pos){
        if (pos->data == data){
            break;
        }
        prev = pos;
        pos = pos->next;
    }

    if (prev == NULL){
        list->head = pos->next;
    } else {
        prev->next = pos->next;
    }
    list->size -= 1;
    free(pos);
}

void insert_pos_list(PLIST list, int pos, KEY_VALUE data){
    if (pos <= 0 || pos > size_list(list)){
        printf("pos invalid :%d \n", pos);
        return;
    }
    PLIST_NODE pos_node = list->head, prev=NULL;

    PLIST_NODE new_node = (PLIST_NODE)calloc(1, sizeof(LIST_NODE));
    new_node->data = data;
    new_node->next = NULL;

    if (pos_node == NULL){
        list->head = new_node;
        list->size += 1;
        return;
    }

    int c = 0;
    while(pos_node){
        if (++c == pos){
            break;
        }
        prev = pos_node;
        pos_node = pos_node->next;
    }
    if (prev == NULL){
        list->head = new_node;
    } else {
        prev->next = new_node;
    }

    new_node->next = pos_node;
    list->size += 1;
}

void reverse_list(PLIST list){
    //PLIST_NODE left = list->head;
    //PLIST_NODE right = NULL;
    //while (left) {
    //    PLIST_NODE r = right;
    //    right = left;

    //    left = left->next;
    //    right->next = r;
    //}
    //list->head = right;

    //两种方式都可以反转
    PLIST_NODE prev = NULL;
    PLIST_NODE curr = list->head;
    while (curr){
        PLIST_NODE next = curr->next;
        curr->next = prev;
        
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

void show_list(PLIST list){
    PLIST_NODE pos = list->head;
    while (pos){
        printf("%d", pos->data);
        if (pos->next){
            printf(" -> ");
        }
        pos = pos->next;
    }
    printf("\n size=%d\n", size_list(list));
}
