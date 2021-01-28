#include <iostream>

using namespace std;
/**
 * 目的是练习单项链表的反转
*/

class ForwardList{
    typedef struct Node{
        int data_;
        struct Node* next_;
    }ListNode;
    int size_;
    ListNode* head_;

    
public:
    ForwardList():size_(0),head_(nullptr){}
    virtual ~ForwardList(){
        ListNode *curr = head_, *tmp;

        while(curr){
            tmp = curr->next_;
            free(curr);
            curr = tmp;
        }
        head_ = nullptr;
        size_ = 0;
    }


    void InsertFront(int data){
        ListNode *newNode = new ListNode();
        newNode->data_ = data;
        newNode->next_ = head_;
        head_ = newNode;
    }
    void Reverse(){
        ListNode *cur=head_, *prev=nullptr, *tmp;
        while(cur){
            tmp = cur->next_;
            cur->next_ = prev;

            prev = cur;
            cur = tmp;
        }
        head_ = prev;
    }
    void Show(){
        ListNode *cur = head_;
        while(cur){
            cout << cur->data_ << " -> ";
            cur = cur->next_;
        }
        cout << endl;
    }
};


int main(){
    ForwardList fl;
    fl.InsertFront(1);
    fl.InsertFront(2);
    fl.InsertFront(3);
    fl.InsertFront(4);

    fl.Show();
    fl.Reverse();
    fl.Show();

    return 0;
}