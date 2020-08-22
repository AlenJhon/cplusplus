#ifndef AL_LIST_GRAPH_CPP_H
#define AL_LIST_GRAPH_CPP_H
#include <list>

/* 用链表表示一个图中不同顶点之间的连接关系，以下代码只是供学习使用，并没有那么的严谨
 *
 * build    g++ list_graph_cpp_test.cpp -std=c++11
 */

namespace al {
class Vertex {
public:
    char label;
    Vertex(char lab):label(lab){}
};

template<typename T>
class Graph {
public:
    Graph(const int vertices);
    ~Graph();

    void AddVertex(char c);
    void AddEdge(int start, int end);

    void PrintVertice();//输出顶点
    void PrintAdjList();
private:
    T** vertexList_;//存放顶点指针   指针数组
    std::list<int>* headNodes_;//存放每个顶点的连接关系  list 数组
    int capacity_;   //容量
    int nVerts_;     //当前顶点数
};

template<typename T>
void Graph<T>::PrintAdjList() {
    for (int i = 0; i < nVerts_; ++i) {
        std::cout << i << "->";
        for (auto x : headNodes_[i]) {
            std::cout << x << "->";
        }
        std::cout << "end" << std::endl;
    }
}

template<typename T>
void Graph<T>::PrintVertice() {
    for (int i = 0; i < nVerts_; ++i) {
        std::cout << (vertexList_[i])->label << " ";
    }
    std::cout << std::endl;
}


template<typename T>
void Graph<T>::AddEdge(int start, int end) {
    headNodes_[start].push_back(end);
}

template<typename T>
void Graph<T>::AddVertex(char c) {
    T* newVertex = new T(c);
    //newVertex->label = v.label;
    vertexList_[nVerts_++] = newVertex;
}

template<typename T>
Graph<T>::~Graph() {
    for (int i = 0; i < nVerts_; ++i) {
        delete vertexList_[i];
    }
    delete[] vertexList_;
    delete[] headNodes_;
}


template<typename T>
Graph<T>::Graph(const int vertices):capacity_(vertices) {
    vertexList_ =  new T*[capacity_];
    headNodes_ = new std::list<int>[capacity_];
    nVerts_ = 0;
}


}

#endif // !AL_LIST_GRAPH_CPP_H
