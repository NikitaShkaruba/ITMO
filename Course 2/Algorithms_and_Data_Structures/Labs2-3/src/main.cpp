#include <iostream>
#include "graph/Graph.h"
#include "graph/GraphBuilder.h"
#include "algorithms/algorithms.h"

using namespace std;

void printHelp() {
    cout << "::HELP::" << endl;
    cout << "Usage pattern for dummies: 'labs2-3 {test/run} --algorithm kruskal'" << endl;
    cout << "Mods: " << endl;
    cout << "* help - print help" << endl << endl;
    cout << "run - use random graph for algorithms" << endl;
    cout << "optional keys:" << endl;
    cout << "--algorithm, -a" << endl;
    cout << "\t dijkstra, d - Dijkstra's algorithm for finding shortest path algorithm" << endl;
    cout << "\t bellmanfor, bf - Bellman-Ford algorithm for finding shortest path" << endl;
    cout << "\t prim, p - Prim's algorithm for finding min spanning tree" << endl;
    cout << "\t kruskal, k - Kruskal's algorithm for finding min spanning tree" << endl;
    cout << "--directed, -d {0/1}" << endl;
    cout << "--vertexAmount, -va {number}" << endl;
    cout << "--edgesAmount, -ea {number}" << endl;
    cout << "--minWeight, -minw {number}" << endl;
    cout << "--maxWeight, -maxw {number}" << endl;
    cout << "--start, -s {vertexId}" << endl;
    cout << "--finish, -f {vertexIdd}" << endl << endl;
    cout << "* test - use test graph for algorithm" << endl;
    cout << "optional keys:" << endl;
    cout << "--algorithm, -a" << endl;
    cout << "\t dijkstra, d - Dijkstra's algorithm for finding shortest path algorithm" << endl;
    cout << "\t bellmanfor, bf - Bellman-Ford algorithm for finding shortest path" << endl;
    cout << "\t prim, p - Prim's algorithm for finding min spanning tree" << endl;
    cout << "\t kruskal, k - Kruskal's algorithm for finding min spanning tree" << endl;
}
void printVertexes(list<Vertex *> path) {
    if (!path.empty()) {
        for (list<Vertex*>::iterator i = path.begin(); i != path.end(); ++i) {
            cout << "{" + to_string((*i)->id) + "} -- ";
        }
    } else {
        cout << "none";
    }

    cout << endl;
}
void runDijkstraTest() {
    cout << "Testing Dijkstra's marked algorithm" << endl;

    GraphBuilder builder(7);
    builder.generateDijkstraTestGraph();
    Graph* g = builder.getResult();

    list<Vertex*> shortestPath = Dijkstra(g, 0, 5);

    cout << "Expected shortest path: \t{0} -- {1} -- {3} -- {5} --" << endl;
    cout << "Output shortest path: \t\t";
    printVertexes(shortestPath);
    cout << endl;
}
void runBellmanFordTest() {
    cout << "Testing Bellman-Ford algorithm" << endl;

    GraphBuilder builder(6);
    builder.generateBellmanFordTestGraph();
    Graph* g = builder.getResult();

    list<Vertex*> shortestPath = BellmanFord(g, 5, 1);


    cout << "Expected shortest path: \t{5} -- {4} -- {3} -- {0} -- {2} -- {1} --" << endl;
    cout << "Output shortest path:\t\t";
    printVertexes(shortestPath);
    cout << endl;
}
void runPrimTest() {
    cout << "Testing Prima's algorithm" << endl;

    GraphBuilder builder(6);
    builder.generatePrimTestGraph();
    Graph* g = builder.getResult();

    Graph* minSpanningTree = Prim(g);
    cout << "Expected vertices, edges amounts: \t(6, (6-1)*2);" << endl;
    cout << "Output vertices, edges amounts: \t(" << minSpanningTree->getVerticesAmount() << ", " << minSpanningTree->getEdgesAmount() << ");" << endl << endl;
}
void runKruskalTest() {
    cout << "Testing Kruskal's algorithm" << endl;

    GraphBuilder builder(7);
    builder.generateKruskalTestGraph();
    Graph* g = builder.getResult();

    Graph* minSpanningTree = Kruskal(g);
    cout << "Expected vertices, edges amounts: \t(7, (7-1)*2);" << endl;
    cout << "Output vertices, edges amounts: \t(" << minSpanningTree->getVerticesAmount() << ", " << minSpanningTree->getEdgesAmount() << ");" << endl << endl;
}
void runAllTests() {
    runDijkstraTest();
    runBellmanFordTest();
    runPrimTest();
    runKruskalTest();
}

void runAlgorithm(map<string, int> options) {
    GraphBuilder builder(options["vertexAmount"]);

    if (options["directed"] == 1)
        builder.generateRandomDirectedGraph(options["vertexAmount"], options["edgesAmount"], options["minWeight"], options["maxWeight"]);
    else
        builder.generateRandomUndirectedGraph(options["vertexAmount"], options["edgesAmount"], options["minWeight"], options["maxWeight"]);

    switch(options["algorithm"]) {
        case 0: {
            list<Vertex *> shortestPath = Dijkstra(builder.getResult(), options["start"], options["finish"]);
            cout << "Shortest path: ";
            printVertexes(shortestPath);
            break;
        }

        case 1: {
            list<Vertex *> shortestPath = BellmanFord(builder.getResult(), options["start"], options["finish"]);
            cout << "Shortest path: ";
            printVertexes(shortestPath);
            break;
        }

        case 2: {
            Graph *minSpanningTree = Prim(builder.getResult());

            cout << "Vertexes count: " << minSpanningTree->getVerticesAmount() << endl;
            cout << "Edges count: " << minSpanningTree->getEdgesAmount() << endl;
            break;
        }

        case 3: {
            Graph *minSpanningTree = Kruskal(builder.getResult());

            cout << "Vertexes count: " << minSpanningTree->getVerticesAmount() << endl;
            cout << "Edges count: " << minSpanningTree->getEdgesAmount();
            break;
        }
    }
}

// Option 31
// 1. Dijkstra's marked algorithm
// 2. Bellman–Ford algorithm
// 3. Prim's algorithm
// 4. Kruskal's algorithm
int main(int argc, char* argv[]) {
    if (argc < 2 || argc % 2 == 1) {
        cout << "Try 'GraphAlgorithms help' for information about usage" << endl;
        return 0;
    }

    map<string, int> customOptions = {{"algorithm", 0}, {"directed", 0}, {"vertexAmount", 10}, {"edgesAmount", 10}, {"minWeight", 0}, {"maxWeight", 100} };
    string key = argv[1];

    if (key == "help") {
        printHelp();
    }
    if (key == "test") {
        for (int i = 2; i < argc; i += 2) {
            string option = argv[i];
            string value = argv[i+1];

            if (option == "--algorithm" || option == "-a") {
                if (value == "all" || value == "a") {
                    runAllTests();
                    continue;
                }
                if (value == "dijkstra" || value == "d") {
                    runDijkstraTest();
                    continue;
                }
                if (value == "bellman-ford" || value == "bf") {
                    runBellmanFordTest();
                    continue;
                }
                if (value == "prim" || value == "p") {
                    runPrimTest();
                    continue;
                }
                if (value == "kruskal" || value == "k") {
                    runKruskalTest();
                    continue;
                }

                cout << "Try 'GraphAlgorithms help' for information about usage" << endl;
                return 1;
            } else {
                cout << "Try 'GraphAlgorithms help' for information about usage" << endl;
                return 1;
            }
        }
        return 0;
    }
    if (key == "run") {
        for (int i = 2; i < argc; i += 2) {
            string option = argv[i];
            string value = argv[i+1];

            if (option == "--algorithm" || option == "-a") {
                if (value == "dijkstra" || value == "d") {
                    customOptions["algorithm"] = 0;
                    continue;
                }
                if (value == "bellman-ford" || value == "bf") {
                    customOptions["algorithm"] = 1;
                    continue;
                }
                if (value == "prim" || value == "p") {
                    customOptions["algorithm"] = 2;
                    continue;
                }
                if (value == "kruskal" || value == "k") {
                    customOptions["algorithm"] = 3;
                    continue;
                }

                cout << "Try 'GraphAlgorithms help' for information about usage" << endl;
                return 1;
            }
            if (option == "--directed" || option == "-d") {
                customOptions["directed"] = stoi(value);
            }
            if (option == "--vertexAmount" || option == "-va") {
                customOptions["vertexAmount"] = stoi(value);
            }
            if (option == "--edgesAmount" || option == "-ea") {
                customOptions["edgesAmount"] = stoi(value);
            }
            if (option == "--minWeight" || option == "-min") {
                customOptions["minWeight"] = stoi(value);
            }
            if (option == "--maxWeight" || option == "-max") {
                customOptions["maxWeight"] = stoi(value);
            }
            if (option == "--start" || option == "-s") {
                customOptions["start"] = stoi(value);
            }
            if (option == "--finish" || option == "-f") {
                customOptions["finish"] = stoi(value);
            }
        }

        if (customOptions["algorithm"] == -1) {
            cout << "Try 'GraphAlgorithms help' for information about usage" << endl;
            return 1;
        } else {
            runAlgorithm(customOptions);
            return 0;
        }
    }

    cout << "Try 'GraphAlgorithms help' for information about usage" << endl;
    return 1;
}
