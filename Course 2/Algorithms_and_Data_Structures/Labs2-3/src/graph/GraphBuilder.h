#pragma once

#include "Graph.h"

class GraphBuilder {
public:
    GraphBuilder(size_t graphSize);
    GraphBuilder(size_t graphSize, int minWeight, int maxWeight);
    void generateTestGraph1();

    void addVertex(string name);
    void addEdges(string sourceName, vector<pair<string, int>> names);
    Graph* getResult();

private:
    Graph* constructed;
    int minWeight;
    int maxWeight;
};


