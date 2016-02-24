#include <iostream>
#include "graph/Graph.h"
#include "graph/GraphBuilder.h"
#include "algorithms/algorithms.h"

using namespace std;

void PrintVertexes(list<Vertex *> path) {
    for (list<Vertex*>::iterator i = path.begin(); i != path.end(); ++i) {
        cout << "{" + (*i)->name + "} -- ";
    }
}

// Option 31
// 1. Dijkstra's marked algorithm
// 2. Bellman–Ford algorithm
int main(int argc, char* argv[]) {
    if (argc == 2) {
        string key = argv[1];

        if (key == "0") {
            cout << "Testing Dijkstra's marked algorithm" << endl;

            GraphBuilder builder(7);
            builder.generateDijkstraTestGraph();
            Graph* g = builder.getResult();

            list<Vertex*> shortestPath = Dijkstra(g, "A", "F");

            cout << "Shortest path: ";
            PrintVertexes(shortestPath);
            return 0;
        }
        if (key == "1") {
            cout << "Testing Bellman-Ford algorithm" << endl;

            GraphBuilder builder(6);
            builder.generateBellmanFordTestGraph();
            Graph* g = builder.getResult();

            list<Vertex*> shortestPath = BellmanFord(g, "S", "B");

            cout << "Shortest path: ";
            PrintVertexes(shortestPath);
            return 0;

            return 0;
        }
        if (key == "help") {
            cout << "::HELP::" << endl;
            cout << "Available keys: " << endl;
            cout << "0 - Dijkstra's algorithm" << endl;
            cout << "1 - Bellman-Ford algorithms" << endl;
            return 0;
        }
    }

    cout << "Try 'Labs2-3 help' for information about usage" << endl;
    return 0;
}
