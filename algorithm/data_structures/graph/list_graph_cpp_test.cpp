#include <iostream>
#include "list_graph_cpp.h"

using namespace std;

int main() {
    al::Graph<al::Vertex> g(5);
    g.AddVertex('A');//0
    g.AddVertex('B');//1
    g.AddVertex('C');//2
    g.AddVertex('D');//3
    g.AddVertex('E');//4

    g.PrintVertice();

    //有个关系图，根据关系图，画边
    g.AddEdge(0, 1);
    g.AddEdge(0, 3);
    g.AddEdge(1, 0);
    g.AddEdge(1, 4);
    g.AddEdge(2, 4);
    g.AddEdge(3, 0);
    g.AddEdge(3, 4);
    g.AddEdge(4, 1);
    g.AddEdge(4, 2);
    g.AddEdge(4, 3);
    g.PrintAdjList();

    return 0;
}