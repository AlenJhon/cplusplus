#ifndef AL_BINARY_BTREE_H
#define AL_BINARY_BTREE_H

/*二叉查找树的简单实现，元素不能重复插入，
 *
 *
*/

#include <queue> //for level order

namespace al {

enum Boolean { FALSE, TRUE };

template<typename Type>
struct Element {
    Type key;
};

template<typename Type> class BSTree;

template<typename Type>
class BstNode {
    friend class BSTree<Type>;
private:
    Element<Type> data_;
    BstNode<Type>* left_;
    BstNode<Type>* right_;

    //test
    void display(int idx);
};

template<typename Type>
void BstNode<Type>::display(int idx) {
    std::cout << "Position: " << idx << ", key=" << data_.key << std::endl;
    //if (left_)
    //    left_->display(2 * idx);
    //if (right_)
    //    right_->display(2 * idx + 1);
}


template<typename Type>
class BSTree {
public:
    BSTree():root_(0){}
    ~BSTree();

    void Clear(BstNode<Type>* curNode);
    Boolean Insert(const Element<Type>& x);
    BstNode<Type>* Search(const Element<Type>& x);//递归查找
    BstNode<Type>* IterSearch(const Element<Type>& x); //遍历查找

    void InOrder();
    void LevelOrder();

private:
    BstNode<Type>* Search(BstNode<Type>* pNode, const Element<Type>& x);
    void InOrder(BstNode<Type>* pNode);

private:
    BstNode<Type>* root_;
};

template<typename Type>
void BSTree<Type>::InOrder() {
    InOrder(root_);
}

template<typename Type>
void BSTree<Type>::LevelOrder() {
    std::queue<BstNode<Type>*> q;
    BstNode<Type>* pos = root_;
    while (pos) {
        std::cout << pos->data_.key << "  ";
        if (pos->left_) {
            q.push(pos->left_);
        }
        if (pos->right_) {
            q.push(pos->right_);
        }
        pos = q.front();
        q.pop();
    }
    std::cout << std::endl;
    return;
}

template<typename Type>
void BSTree<Type>::InOrder(BstNode<Type>* pNode) {
    if (pNode) {
        InOrder(pNode->left_);
        std::cout << pNode->data_.key << "  ";
        InOrder(pNode->right_);
    }
}


template<typename Type>
Boolean BSTree<Type>::Insert(const Element<Type>& x) {
    BstNode<Type>* p = root_;
    BstNode<Type>* q = 0;
    while (p) {
        q = p;
        if (x.key == p->data_.key) { return FALSE; }
        if (x.key < p->data_.key) { p = p->left_; }
        else { p = p->right_; }
    }

    p = new BstNode<Type>;
    p->data_ = x; // copy constructor;
    p->left_ = p->right_ = 0;

    if (!root_) { root_ = p; }
    else if (x.key < q->data_.key) { q->left_ = p; }
    else { q->right_ = p; }
        
    return TRUE;
}

template<typename Type>
BstNode<Type>* BSTree<Type>::Search(const Element<Type>& x) {
    return Search(root_, x);
}

template<typename Type>
BstNode<Type>* BSTree<Type>::IterSearch(const Element<Type>& x) {
    BstNode<Type>* pos = root_;
    while (pos) {
        if (x.key == pos->data_.key)
            return pos;
        else if (x.key < pos->data_.key)
            pos = pos->left_;
        else
            pos = pos->right_;
    }
    return 0;
}

template<typename Type>
BstNode<Type>* BSTree<Type>::Search(BstNode<Type>* pNode, const Element<Type>& x) {
    if (!pNode) { 
        return 0; 
    }

    if (x.key == pNode->data_.key) { 
        return pNode; 
    }
    else if (x.key < pNode->data_.key) {
        return Search(pNode->left_, x);
    }
    return Search(pNode->right_, x);
}


template<typename Type>
BSTree<Type>::~BSTree() {
    Clear(root_);
}

template<typename Type>
void BSTree<Type>::Clear(BstNode<Type>* curNode) {
    if (curNode) {
        if (curNode->left_) {
            Clear(curNode->left_);
        }
        if (curNode->right_) {
            Clear(curNode->right_);
        }
        delete curNode;
    }
}




}

#endif // !AL_BINARY_BTREE_H
