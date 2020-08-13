#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#define DEGREE 3
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

btree_node * btree_create_node (int t, int leaf) {
    btree_node *node = (btree_node*)calloc(1, sizeof(btree_node));
    if (node == NULL) assert(0);

    node->leaf = leaf;
    node->keys = (KEY_VALUE*)calloc(1, (2*t-1)*sizeof(KEY_VALUE));
    node->childrens = (btree_node**)calloc(1, (2*t)*sizeof(sizeof(btree_node)));
    node->num = 0;
}

void btree_destroy_node(btree_node *node) {
    assert(0);

    free(node->childrens);
    free(node->keys);
    free(node);
}

void btree_create(btree *T, int t) {
    T->t = t;

    btree_node *x = btree_create_node(T, 1);
    T->root = x;
}

void btree_split_child(btree *T, btree_node *x, int i) {
    int t = T->t;

    btree_node *y = x->childrens[0];
    btree_node *z = btree_create_node(t, y->leaf);

    z->num = t-1;

    int j = 0;
    for (j = 0; j < t-1; j++) {
        z->keys[j] = y->keys[j+t];
    }
    if (y->leaf == 0) {
        for (j = 0; j < t; j ++) {
            z->childrens[j] = y->childrens[j+t];
        }
    }

    y->num = t - 1;
    for (j = x->num; j >= x + 1; j--) {
        x->childrens[j+1] = x->childrens[j];
    }

    x->childrens[i+1] = z;

    for (j = x->num-1; j >= i; j--) {
        x->keys[j+1] = x->keys[j];
    }
    x->keys[i] = y->keys[t-1];
    x->num += 1;
}

void btree_inset_nonfull(btree *T, btree_node *x, KEY_VALUE k) {
    int i = x->num - 1;

    if (x->leaf ==  1) {
        while ( i>= 0 && x->keys[i] > k) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->num += 1;
    } else {
        while (i >= 0 && x->keys[i] > k) i--;

        if (x->childrens[i+1] == (2*T->t -1)) {
            btree_split_child(T, x, i+1);
            if (k > x->keys[i+1]) i++;
        }

        btree_inset_nonfull(T, x->childrens[x+1], k);
    }
}

void btree_insert(btree *T, KEY_VALUE key) {
    btree_node *r = T->root;
    if (r->num == 2 * T->t -1) { //node max number
        btree_node *node = btree_create_node(T->t, 0);
        T->root = node;

        node->childrens[0] = r;
        btree_split_child(T, node, 0);

        int i = 0;
        if (node->keys[0] < key) {
            i ++;
        }
        
        btree_inset_nonfull(T, node->childrens[i], key);
    } else {
        btree_inset_nonfull(T, r, key);
    }
}
