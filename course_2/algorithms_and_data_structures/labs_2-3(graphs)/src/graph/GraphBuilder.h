#pragma once

#include "Graph.h"

class GraphBuilder {
public:
    GraphBuilder(size_t graphSize); // Начать конструировать новый граф
    GraphBuilder(Graph* graph);     // Изменить существующий граф

    // Сгенерировать тестовые графы, на которых я теоретически знаю, как работают алгоритмы 
    void generateRandomDirectedGraph(size_t verticesCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight);
    void generateRandomUndirectedGraph(size_t verticesCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight);

    void generateDijkstraTestGraph();
    void generateBellmanFordTestGraph();
    void generatePrimTestGraph();
    void generateKruskalTestGraph();

    void copyGraph(Graph& graph);

    void addVertex(size_t id);
    void addEdge(size_t startId, size_t destinationId, int weight);
    void addUndirectedEdge(size_t firstId, size_t secondId, int weight);
    void removeLoops();
    void removeDoubles();

    Graph* getResult();

private:
    void addEdges(size_t sourceId, vector<pair<size_t, int>> ids);

    Graph* constructed;
};


