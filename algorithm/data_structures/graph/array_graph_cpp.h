#ifndef AL_ARRAY_GRAPH_CPP_H
#define AL_ARRAY_GRAPH_CPP_H
#include <stack>

/* �ö�ά����洢ͼ�и�������֮��Ĺ�ϵ����һ�ֱȽ��˷ѿռ�ķ�ʽ��ֻ���ṩѧϰʹ�ã�
 * Ϊ�˹۲�DFS�����Ĺ���
 * DFS������������㷨�����㷨����Ҫʹ�ó����ǣ���ͼ����AB�����Ƿ���ͨ
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
        int adjMat_[max_verts][max_verts];   //�˷ѿռ�
    };

    void GraphArray::PrintMatrix() {
        for (int i = 0; i < nVerts_; ++i) {
            for (int j = 0; j < nVerts_; ++j) {
                std::cout << adjMat_[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    //������������㷨 ��������ջ�����ݽṹʵ�ֱ���
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
