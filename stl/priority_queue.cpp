#include <iostream>
#include <queue>

struct HeapNode{
    int data;
    HeapNode(int d):data(d) {}
};

struct HeapNodeCmp {
    bool operator()(const HeapNode& a, const HeapNode& b) {
        return a.data > b.data;
    }
};


int main(){
    
    std::priority_queue<int> mypq;
    mypq.push(30);
    mypq.push(100);
    std::cout << "top=" << mypq.top() << std::endl;
    mypq.push(40);
    mypq.push(140);
    mypq.push(240);
    mypq.push(340);
    mypq.push(440);
    std::cout << "top=" << mypq.top() << " , size=" << mypq.size() << std::endl;

    //mypq.pop_back();
    //std::cout << "top=" << mypq.top() << std::endl;


    std::cout << "========================================2" << std::endl;
    // Î¬³ÖN×îÐ¡¶Ñ
    std::priority_queue<HeapNode, std::vector<HeapNode>, HeapNodeCmp> minheap;
    HeapNode node(100);
    minheap.push(node);
    HeapNode node2(10);
    minheap.push(node2);
    //std::cout << minheap.top().data << std::endl;
    int arr[] = { 1000,120, 130, 500, 400 };
    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
        if (minheap.size() < 3) {
            minheap.push(HeapNode(arr[i]));
        } else {
            if (arr[i] > minheap.top().data ) {
                minheap.pop();
                minheap.push(HeapNode(arr[i]));
            }
        }
    }
    while (!minheap.empty()) {
        std::cout << minheap.top().data << std::endl;
        minheap.pop();
    }

   



    //std::cout << "========================================3" << std::endl;
    //std::priority_queue<int> mypq3;
    //mypq3.


    return 0;
}
