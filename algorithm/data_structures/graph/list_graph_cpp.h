#ifndef AL_LIST_GRAPH_CPP_H
#define AL_LIST_GRAPH_CPP_H
#include <list>

/* �������ʾһ��ͼ�в�ͬ����֮������ӹ�ϵ�����´���ֻ�ǹ�ѧϰʹ�ã���û����ô���Ͻ�
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

    void PrintVertice();//�������
    void PrintAdjList();
private:
    T** vertexList_;//��Ŷ���ָ��   ָ������
    std::list<int>* headNodes_;//���ÿ����������ӹ�ϵ  list ����
    int capacity_;   //����
    int nVerts_;     //��ǰ������
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
