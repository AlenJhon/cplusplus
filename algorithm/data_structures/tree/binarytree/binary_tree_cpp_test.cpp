#include <iostream>
#include "binary_tree_cpp.h"

using namespace std;

int main() {
    cout << "Test binary tree ." << endl;
    // al::BSTree<int> bst;

    // int a[] = { 10, 5, 11, 4, 7 };
    // al::Element<int> e;
    // for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
    //     e.key = a[i];
    //     bst.Insert(e);
    // }

    // cout << "in order : ";
    // bst.InOrder();
    // cout << endl;

    // e.key = 7;
    // cout << "find 7 result=" << bst.Search(e) << endl;
    // cout << "IterSearch find 7 result=" << bst.IterSearch(e) << endl;

    // e.key = 71;
    // cout << "find 71 result=" << bst.Search(e) << endl;
    // cout << "IterSearch find 71 result=" << bst.IterSearch(e) << endl;

    // cout << "level order : ";
    // bst.LevelOrder();

    
    //case pre
    al::BSTree<int> bst;
    al::Element<int> e;
    //for(auto& it : {1,2,3,4,5,6,7}){//是因为这组数据退化成链表了,所以前序,中序,层序都是一样的
    for(auto& it : {10, 5, 11, 4, 7}) {
        e.key = it;
        bst.Insert(e);
    }
    cout << "level order : ";
    bst.LevelOrder();
    cout << "in order " << endl;
    bst.InOrder();
    cout << "\npre order " << endl;
    bst.PreOrder();


    return 0;
}