#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED     1   
#define BLACK   2

typedef int KEY_VALUE;

typedef struct _rbtree_node {
    unsigned char color;
    struct _rbtree_node *left;
    struct _rbtree_node *right;
    struct _rbtree_node *parent;
    KEY_VALUE key;
    void *value;
}rbtree_node;

typedef struct _rbtree {
    rbtree_node *root;
    rbtree_node *nil;
}rbtree;

rbtree_node *rbtree_mini(rbtree *T, rbtree_node *x) {
    while (x->left != T->nil) {
        x = x->left;
    }
    return x;
}

rbtree_node *rbtree_maxi(rbtree *T, rbtree_node *x) {
    while (x->right != T->nil) {
        x = x->right;
    }
    return x;
}

//find x node next successor
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

void rbtree_insert_fixup(rbtree *T, rbtree_node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rbtree_node *y = z->parent->parent->right;
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
            return ;
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
    z->color = RED;

    rbtree_insert_fixup(T, z);
}

void rbtree_delete_fixup(rbtree *T, rbtree_node *x) {

}

    rbtree_node *
    rbtree_delete(rbtree *T, rbtree_node *z)
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
    if (x != T->nil) {
        x->parent = y->parent;
    }
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

void rbtree_traversal(rbtree *T, rbtree_node *node) {
    if (node != T->nil) {
        rbtree_traversal(T, node->left);
        printf("key:%d, color:%d\n", node->key, node->color);
        rbtree_traversal(T, node->right);
    }
}


int main() {

    int keyArray[20] = {24, 25, 13, 35, 23, 26, 67, 47, 38, 98, 20, 19, 17, 49, 12, 21, 9, 18, 14, 15};
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
    for (i = 0; i < 20; i++) {
        node = (rbtree_node *)malloc(sizeof(rbtree_node));
        node->key = keyArray[i];
        node->value = NULL;

        rbtree_insert(T, node);
    }

    rbtree_traversal(T, T->root);
    printf("+++++++++++++++++++++++++++++++++++++++\n");

    for (i = 0; i < 20; i++) {
        rbtree_node *node = rbtree_search(T, keyArray[i]);
        rbtree_node *pur = rbtree_delete(T, node);
        free(pur);

        rbtree_traversal(T, T->root);
        printf("idx:%d, key:%d\n", i, keyArray[i]);
    }

    return 0;
}