#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED     1   
#define BLACK   2

typedef int KEY_VALUE;

//代表每个结点
typedef struct _rbtree_node {
    unsigned char color;
    struct _rbtree_node *left;
    struct _rbtree_node *right;
    struct _rbtree_node *parent;
    KEY_VALUE key;
    void *value;
}rbtree_node;

//代表红黑树结构
typedef struct _rbtree {
    rbtree_node *root; //指向根节点
    rbtree_node *nil; //代表nil结点 会申请一个节点color=BLACK
}rbtree;

//查找当前子树下最小的结点
rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x) {
    while (x->left != T->nil) {
        x = x->left;
    }
    return x;
}

//查找当前子树下最大的结点
rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x) {
    while (x->right != T->nil) {
        x = x->right;
    }
    return x;
}

//find x node next successor
//查找当前结点后继结点 
rbtree_node *rbtree_successor(rbtree *T, rbtree_node *x) {
    rbtree_node *y = x->parent;

    if (x->right != T->nil) { // 查找比x大的集合中，最小的那一个
        return rbtree_mini(T, x->right);
    }

    //找比x小的 最大的那一个
    while ( (y != T->nil) && (x == y->right)) {
        x = y;
        y = y->parent;
    }
    return y;
}

//change six ptr 
// 左旋
void rbtree_left_rotate(rbtree *T, rbtree_node *x) {
    rbtree_node *y = x->right;

    x->right = y->left; // step 1
    if (y->left != T->nil) {
        y->left->parent = x; // step 2
    }

    y->parent = x->parent; // step 3
    //step 4
    if (x->parent == T->nil) {
        T->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    // } else if (x == x->parent->right) {
    //     x->parent->right = y;
    // }

    y->left = x; // step 5
    x->parent = y; // step 6

}

void rbtree_right_rotate(rbtree *T, rbtree_node *y) {
    rbtree_node *x = y->left;

    y->left = x->right; // step 1
    if (x->right != T->nil) {//step 2
        x->right->parent = y;
    }

    x->parent = y->parent;//step 3
    if (y->parent == T->nil) { // step 4
        T->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    // } else if (y == y->parent->right) {
    //     y->parent->right = x;
    // }

    x->right = y; // step 5
    y->parent = x; // step 6

}

void rbtree_insert_fixup(rbtree *T, rbtree_node *z) {//z 是插入节点
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) { // z 的父亲是祖父的左孩子
            rbtree_node *y = z->parent->parent->right; //叔父
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rbtree_left_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);
            }
        } else {
            rbtree_node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            } else {
                if ( z == z->parent->left) {
                    z = z->parent;
                    rbtree_right_rotate(T, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void rbtree_insert(rbtree *T, rbtree_node *z) {
    rbtree_node *y = T->nil;
    rbtree_node *x = T->root;

    while (x != T->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else { // Exist
            printf("key:%d exists.\n", z->key);
            return ;   //这里没有对存在的数据进行处理直接给返回了
        }
    }

    z->parent = y;
    if (y == T->nil) {
        T->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = T->nil;
    z->right = T->nil;
    z->color = RED; //插入的结点都是红色结点,尽量不影响黑高

    //插入后修复平衡
    rbtree_insert_fixup(T, z);
}

void rbtree_delete_fixup(rbtree *T, rbtree_node *x) {
    while ((x != T->root) && (x->color == BLACK)) {
        if (x == x->parent->left) {
            rbtree_node *w = x->parent->right; //兄弟结点 
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;

                rbtree_left_rotate(T, x->parent);
                w = x->parent->right;
            }

            // left right black
            if ((w->left->color  == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else { 
                if (w->right->color == BLACK) { // right black
                    w->left->color = BLACK;
                    w->color = RED;
                    rbtree_right_rotate(T, w);
                    w = x->parent->right;
                }

                //left black
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbtree_left_rotate(T, x->parent);
                
                x = T->root;
            }
        }else { // x right child
            rbtree_node *w = x->parent->left; // brother
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(T, x->parent);
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(T, w);
                    w = x->parent->left;
                }

                //right black
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, x->parent);

                x  = T->root;
            }
         }
    }
}

rbtree_node *rbtree_delete(rbtree *T, rbtree_node *z)
{
    rbtree_node *y = T->nil;
    rbtree_node *x = T->nil;

    //find y
    if ( (z->left == T->nil) || (z->right == T->nil)) {
        y = z;
    } else {
        y = rbtree_successor(T, z);
    }

    //find x
    if (y->left != T->nil) {
        x = y->left;
    } else if (y->right != T->nil) {
        x = y->right;
    }

    //delete y
    //if (x != T->nil) {
    //    x->parent = y->parent;
    //}
    x->parent = y->parent;
    if (y->parent == T->nil) {
        T->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    //recover z / remove z
    if (y != z) {
        z->key = y->key;
        z->value = y->value;
    }

    //后继节点被删除的是黑色的,相当于是黑色节点移动了，影响了左右子树的黑高,需要调整
    if (y->color == BLACK) {
        rbtree_delete_fixup(T, x);
    }

    return y;
}

rbtree_node * rbtree_search(rbtree *T, KEY_VALUE key) {
    rbtree_node *node = T->root;
    while (node != T->nil) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return node;
        }
    }
    return T->nil;
}

void rbtree_traversal(rbtree *T, rbtree_node *node, int idx) {
    if (node != T->nil) {
        rbtree_traversal(T, node->left, 2*idx + 1);
        if (node != T->nil) {
            printf("key:%d, idx:%d color:%s\n", node->key, idx, node->color == RED ? "RED" : "BLACK");
        }
        rbtree_traversal(T, node->right, 2*idx + 2);
    }
}


int main() {

    int keyArray[] = {15, 23, 77, 32, 65, 18, 89, 43};
    int arrLen = sizeof(keyArray) / sizeof(int);

    rbtree *T = (rbtree *)malloc(sizeof(rbtree));
    if (T ==  NULL) {
        printf("malloc failed\n");
        return -1;
    }

    T->nil = (rbtree_node *)malloc(sizeof(rbtree_node));
    T->nil->color = BLACK;
    T->root = T->nil;

    rbtree_node *node = T->nil;
    int i = 0;
    for (i = 0; i < arrLen; i++) {
        node = (rbtree_node *)malloc(sizeof(rbtree_node));
        node->key = keyArray[i];
        node->value = NULL;

        rbtree_insert(T, node);
    }

    rbtree_traversal(T, T->root, 0);
    //printf("+++++++++++++++++++++++++++++++++++++++\n");

    //for (i = 0; i < arrLen; i++) {
    //    rbtree_node* node = rbtree_search(T, keyArray[i]);
    //    if (node != T->nil) {
    //        printf("rbtree_search %d ok\n", keyArray[i]);
    //    }
    //    else {
    //        printf("rbtree_search %d failed\n", keyArray[i]);
    //    }
    //    rbtree_node* pur = rbtree_delete(T, node);
    //    free(pur);

    //    rbtree_traversal(T, T->root);
    //    printf("idx:%d, key:%d\n", i, keyArray[i]);
    //}

    return 0;
}