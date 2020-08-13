#include <iostream>
#include "binary_tree_cpp.h"

using namespace std;

int main() {
    cout << "Test binary tree ." << endl;
    al::BSTree<int> bst;

    int a[] = { 10, 5, 11, 4, 7 };
    al::Element<int> e;
    for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
        e.key = a[i];
        bst.Insert(e);
    }

    cout << "in order : ";
    bst.InOrder();
    cout << endl;

    e.key = 7;
    cout << "find 7 result=" << bst.Search(e) << endl;
    cout << "IterSearch find 7 result=" << bst.IterSearch(e) << endl;

    e.key = 71;
    cout << "find 71 result=" << bst.Search(e) << endl;
    cout << "IterSearch find 71 result=" << bst.IterSearch(e) << endl;

    cout << "level order : ";
    bst.LevelOrder();


    return 0;
}