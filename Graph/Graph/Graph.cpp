//Бусыгина Татьяна, ИВТ-22

#include <iostream>
#include "Graph_mod.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Graph<string> g;

    g.insertVertex("A");
    g.insertVertex("B");
    g.insertVertex("C");
    g.insertVertex("D");
    g.insertVertex("E");

    g.insertEdge("A", "B", 10);
    g.insertEdge("A", "C", 5);
    g.insertEdge("B", "C", 2);
    g.insertEdge("B", "D", 1);
    g.insertEdge("C", "D", 9);
    g.insertEdge("D", "E", 4);

    g.depthFirstSearch("A");
    g.BFS("A");
    g.dijkstra("A");

    return 0;
}