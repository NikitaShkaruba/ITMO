#pragma once

#include "Graph.h"

class GraphBuilder {
public:
    GraphBuilder(size_t graphSize);
    GraphBuilder(Graph* graph);

    void generateRandomDirectedGraph(size_t verticesCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight);
    void generateRandomUndirectedGraph(size_t verticesCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight);

    void generateDijkstraTestGraph();
    void generateBellmanFordTestGraph();
    void generatePrimTestGraph();
    void generateKruskalTestGraph();

    void addVertex(int id);
    void addEdge(int startId, int destinationId, int weight);
    void addUndirectedEdge(int firstId, int secondId, int weight);
    void removeLoops();
    void removeDoubles();

    Graph* getResult();

private:
    void addEdges(int sourceId, vector<pair<int, int>> ids);

    Graph* constructed;
};


