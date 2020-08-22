#include <iostream>
#include "array_graph_cpp.h"

using namespace std;

int main() {
    al::GraphArray ga;

    ga.AddVertex('A');
    ga.AddVertex('B');
    ga.AddVertex('C');
    ga.AddVertex('D');
    ga.AddVertex('E');

    ga.AddEdge(0, 1); // A-B
    ga.AddEdge(0, 3); // A-D
    ga.AddEdge(1, 0); // B-A
    ga.AddEdge(1, 4); // B-E
    ga.AddEdge(2, 4); // C-E
    ga.AddEdge(3, 0); // D-A
    ga.AddEdge(3, 4); // D-E
    ga.AddEdge(4, 1);
    ga.AddEdge(4, 2);
    ga.AddEdge(4, 3);

    ga.PrintMatrix();

    cout << "DFS Result:";
    ga.DFS();
    cout << "BFS Result:";
    ga.BFS();
    cout << endl;

    return 0;
}
