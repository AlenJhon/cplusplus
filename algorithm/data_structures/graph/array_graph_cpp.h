#ifndef AL_ARRAY_GRAPH_CPP_H
#define AL_ARRAY_GRAPH_CPP_H
#include <stack>

/* 用二维数组存储图中各个顶点之间的关系，是一种比较浪费空间的方式，只是提供学习使用，
 * 为了观察DFS遍历的过程
 * DFS深度优先搜索算法，该算法的主要使用场景是，在图中找AB两点是否能通
 */

namespace al {
    const int max_verts = 20;
    struct VertexArray {
        VertexArray(char lab) :label_(lab),visited_(false){}
        
        bool visited_;
        char label_;
    };

    class GraphArray {
    public:
        GraphArray();
        ~GraphArray();

        void AddVertex(char c);
        void AddEdge(int start, int end);

        void PrintMatrix();
        void ShowVertex(int v);
        void DFS();
    private:
        int GetAdjUnvisitedVertex(int x);

        VertexArray* vertexList_[max_verts];
        int nVerts_;
        int adjMat_[max_verts][max_verts];   //浪费空间
    };

    void GraphArray::PrintMatrix() {
        for (int i = 0; i < nVerts_; ++i) {
            for (int j = 0; j < nVerts_; ++j) {
                std::cout << adjMat_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    //深度优先搜索算法 ，借用了栈的数据结构实现遍历
    void GraphArray::DFS() {
        std::stack<int> s;
        vertexList_[0]->visited_ = true;
        ShowVertex(0);
        s.push(0);
        int next;
        while (s.size() > 0) {
            next = GetAdjUnvisitedVertex(s.top());
            if (-1 == next) {
                s.pop();
            } else {
                vertexList_[next]->visited_ = true;
                ShowVertex(next);
                s.push(next);
            }
        }
        std::cout << std::endl;

        for (int i = 0; i < nVerts_; ++i) {
            vertexList_[i]->visited_ = false;
        }
    }

    int GraphArray::GetAdjUnvisitedVertex(int x) {
        for (int j = 0; j < nVerts_; ++j) {
            if ((adjMat_[x][j] == 1) && (vertexList_[j]->visited_ == false)) {
                return j;
            }
        }
        return -1;
    }

    void GraphArray::ShowVertex(int v) {
        std::cout << vertexList_[v]->label_ << " ";
    }

    void GraphArray::AddVertex(char c) {
        vertexList_[nVerts_++] = new VertexArray(c);
    }

    void GraphArray::AddEdge(int start, int end) {
        adjMat_[start][end] = 1;
        adjMat_[end][start] = 1;
    }

    GraphArray::GraphArray() {
        nVerts_ = 0;
        for (int i = 0; i < max_verts; ++i) {
            for (int j = 0; j < max_verts; ++j) {
                adjMat_[i][j] = 0;
            }
        }
    }
    GraphArray::~GraphArray() {
        for (int i = 0; i < nVerts_; ++i) {
            delete vertexList_[i];
        }
    }


}

#endif // !AL_ARRAY_GRAPH_CPP_H
