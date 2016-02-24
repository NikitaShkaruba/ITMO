#pragma once

#include "Graph.h"

class GraphBuilder {
public:
    GraphBuilder(size_t graphSize);
    GraphBuilder(size_t graphSize, int minWeight, int maxWeight);

    void generateDijkstraTestGraph();
    void generateBellmanFordTestGraph();
    void generatePrimTestGraph();

    void addVertex(string name);
    void tryIncreaseEdgesCount(string sourceName, string destinationName);
    void addEdge(string sourceName, string destinationName, int weight);
    void addEdges(string sourceName, vector<pair<string, int>> names);
    size_t getCurrentGraphVertexesAmount();
    Graph* getResult();

private:
    Graph* constructed;
    int minWeight;
    int maxWeight;
};


