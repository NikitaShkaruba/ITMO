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

        if (key == "help") {
            cout << "::HELP::" << endl;
            cout << "Usage pattern: 'labs2-3 test 1'" << endl;
            cout << "Available keys: " << endl;
            cout << "custom - use custom graphs for algorithms" << endl;
            cout << "\t not yet implemented :)";
            cout << "test - use algorithms for predefined test cases";
            cout << "\t 0 - Dijkstra's algorithm for finding shortest path algorithm" << endl;
            cout << "\t 1 - Bellman-Ford algorithm for finding shortest path" << endl;
            cout << "\t 2 - Prim's algorithm for finding min spanning tree" << endl;
            cout << "\t 3 - Kruskal's algorithm for finding min spanning tree" << endl;
            return 0;
        }
    }
    if (argc == 3 && string(argv[1]) == "custom") {
        string key = argv[2];
    }
    if (argc == 3 && string(argv[1]) == "test") {
        string key = argv[2];

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
        }
        if (key =="2") {
            cout << "Testing Prima's algorithm" << endl;

            GraphBuilder builder(6);
            builder.generatePrimTestGraph();
            Graph* g = builder.getResult();

            Graph* minSpanningTree = Prim(g, "A");
            cout << "Vertexes count: " << minSpanningTree->getVertexAmount() << cout;
            cout << "Edges count: " << minSpanningTree->getVertexAmount() << cout;
            return 0;
        }
    }

    cout << "Try 'Labs2-3 help' for information about usage" << endl;
    return 0;
}
