#pragma once

#include "Graph.h"

class GraphBuilder {
public:
    GraphBuilder(size_t graphSize);

    void generateRandomDirectedGraph(size_t vertexCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight);
    void generateRandomUndirectedGraph(size_t vertexCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight);
    void generateDijkstraTestGraph();
    void generateBellmanFordTestGraph();
    void generatePrimTestGraph();
    void generateKruskalTestGraph();

    void addVertex(string name);
    void addEdge(string sourceName, string destinationName, int weight);
    void addUndirectedEdge(string vertexName1, string vertexName2, int weight);
    void addEdges(string sourceName, vector<pair<string, int>> names);

    size_t getCurrentGraphVertexesAmount();
    Graph* getResult();

private:
    Graph* constructed;
    int minWeight;
    int maxWeight;
};


