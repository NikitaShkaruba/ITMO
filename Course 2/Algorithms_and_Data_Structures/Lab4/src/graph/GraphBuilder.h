#pragma once

#include "Graph.h"

class GraphBuilder {
public:
    GraphBuilder(size_t graphSize);
    GraphBuilder(Graph* graph);

    void generateTestWeb();
    void generateOptionWeb();
    void generateFlowTestGraph();

    void copyGraph(Graph& graph);

    void addVertex(size_t id);
    void addEdge(size_t startId, size_t destinationId, int weight);
    void addUndirectedEdge(size_t firstId, size_t secondId, int weight);
    void removeEdge(Edge* edge);

    Edge* getOppositeEdge(Edge*);
    void removeLoops();
    void removeDoubles();

    Graph* getResult();

private:
    void addEdges(size_t sourceId, vector<pair<size_t, int>> ids);

    Graph* constructed;

    void addUndirectedEdges(size_t sourceId, vector<pair<size_t, int>> ids);
};


