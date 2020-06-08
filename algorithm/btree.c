

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DEGREE  3
typedef int KEY_VALUE;

typedef struct _btree_node {
    KEY_VALUE *keys;
    struct _btree_node **childrens;
    int num;
    int leaf;
}btree_node;

typedef struct _btree {
    btree_node *root;
    int t;
}btree;

btree_node *btree_create_node(int t, int leaf) {
    btree_node *node = (btree_node*)calloc(1, sizeof(btree_node));
    if (node == NULL) assert(0);

    node->leaf = leaf;
    node->keys = (KEY_VALUE*)calloc(1, (2*t-1)*sizeof(KEY_VALUE));
    node->childrens = (btree_node**)calloc(1, (2*t)*sizeof(btree_node*));
    node->num = 0;

    return node;
}

void btree_destroy_node(btree_node *node) {
    // assert(node);
    if (!node) return;

    free(node->childrens);
    free(node->keys);
    free(node);
}

void btree_create(btree *T, int t) {
    T->t = t;

    btree_node *x = btree_create_node(t, 1);
    T->root = x;
}

void btree_insert(btree *T, KEY_VALUE) {
    btree_node *r = T->root;
    if (r->num == 2 * T->t - 1) {
        btree_node *node = btree_create_node(T->t, 0);
        T->root = node;

        node->childrens[0] = r;
        
    }
}