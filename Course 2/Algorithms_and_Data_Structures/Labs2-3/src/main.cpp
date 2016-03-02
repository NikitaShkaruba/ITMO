#include <iostream>
#include "graph/Graph.h"
#include "graph/GraphBuilder.h"
#include "algorithms/algorithms.h"

using namespace std;

void PrintVertexes(list<Vertex *> path) {
    for (list<Vertex*>::iterator i = path.begin(); i != path.end(); ++i) {
        cout << "{" + to_string((*i)->id) + "} -- ";
    }
}

// Option 31
// 1. Dijkstra's marked algorithm
// 2. Bellman–Ford algorithm
// 3. Prim's algorithm
// 4. Kruskal's algorithm
int main(int argc, char* argv[]) {
    if (argc == 2) {
        string key = argv[1];

        if (key == "help") {
            cout << "::HELP::" << endl;
            cout << "Usage pattern for dummies: 'labs2-3 test 1'" << endl;
            cout << "Available keys: " << endl;
            cout << "custom - use custom graphs for algorithms" << endl;
            cout << "\t * - not yet implemented :)" << endl;
            cout << "test - use algorithms for predefined test cases" << endl;
            cout << "\t 0 - Dijkstra's algorithm for finding shortest path algorithm" << endl;
            cout << "\t 1 - Bellman-Ford algorithm for finding shortest path" << endl;
            cout << "\t 2 - Prim's algorithm for finding min spanning tree" << endl;
            cout << "\t 3 - Kruskal's algorithm for finding min spanning tree" << endl;
            return 0;
        }
    }
    if (argc == 7 && string(argv[1]) == "custom") {
        string key = argv[2];

        size_t vertexCount = (size_t) stoi(argv[3]);
        size_t edgesCount = (size_t) stoi(argv[4]);
        int minEdgeWeight = stoi(argv[5]);
        int maxEdgeWeight = stoi(argv[6]);

        GraphBuilder builder(vertexCount);
        builder.generateRandomUndirectedGraph(vertexCount, edgesCount, minEdgeWeight, maxEdgeWeight);
        Graph* customGraph = builder.getResult();

        if (key == "0") {
            cout << "Testing Dijkstra's marked algorithm" << endl;

            list<Vertex*> shortestPath = Dijkstra(customGraph, customGraph->getRandomVertex()->id, customGraph->getRandomVertex()->id);

            cout << "Shortest path: ";
            PrintVertexes(shortestPath);
            return 0;
        }
        if (key == "1") {
            cout << "Testing Bellman-Ford algorithm" << endl;

            list<Vertex*> shortestPath = BellmanFord(customGraph,customGraph->getRandomVertex()->id, customGraph->getRandomVertex()->id);
            cout << "Shortest path: ";
            PrintVertexes(shortestPath);
            return 0;
        }
    }
    if (argc == 3 && string(argv[1]) == "test") {
        string key = argv[2];

        if (key == "0") {
            cout << "Testing Dijkstra's marked algorithm" << endl;

            GraphBuilder builder(7);
            builder.generateDijkstraTestGraph();
            Graph* g = builder.getResult();

            list<Vertex*> shortestPath = Dijkstra(g, 0, 5);

            cout << "Shortest path: ";
            PrintVertexes(shortestPath);
            return 0;
        }
        if (key == "1") {
            cout << "Testing Bellman-Ford algorithm" << endl;

            GraphBuilder builder(6);
            builder.generateBellmanFordTestGraph();
            Graph* g = builder.getResult();

            list<Vertex*> shortestPath = BellmanFord(g, 5, 1);

            cout << "Shortest path: ";
            PrintVertexes(shortestPath);
            return 0;
        }
        if (key =="2") {
            cout << "Testing Prima's algorithm" << endl;

            GraphBuilder builder(6);
            builder.generatePrimTestGraph();
            Graph* g = builder.getResult();

            Graph* minSpanningTree = Prim(g, 0);
            cout << "Vertexes count: " << minSpanningTree->getVertexAmount() << endl;
            cout << "Edges count: " << minSpanningTree->getVertexAmount() << endl;
            return 0;
        }
        if (key == "3") {
            cout << "Testing Kruskal's algorithm" << endl;

            GraphBuilder builder(7);
            builder.generateKruskalTestGraph();
            Graph* g = builder.getResult();

            Graph* minSpanningTree = Kruskal(g);
            cout << "Vertexes count: " << minSpanningTree->getVertexAmount() << endl;
            cout << "Edges count: " << minSpanningTree->getVertexAmount() << endl;
            return 0;
        }
    }

    cout << "Try 'Labs2-3 help' for information about usage" << endl;
    return 0;
}
