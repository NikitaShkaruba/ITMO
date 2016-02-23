#include "GraphBuilder.h"

void GraphBuilder::generateTestGraph1() {
    addVertex("A"); // start
    addVertex("B");
    addVertex("C");
    addVertex("D");
    addVertex("E");
    addVertex("F"); // destination
    addVertex("G");

    addEdges("A", {{"B", 4}, {"C", 3}, {"E", 7}});
    addEdges("B", {{"A", 4}, {"C", 6}, {"D", 5}});
    addEdges("C", {{"A", 3}, {"B", 6}, {"D", 11}, {"E", 8}});
    addEdges("D", {{"B", 5}, {"C", 11}, {"E", 2}, {"G", 10}, {"F", 2}});
    addEdges("E", {{"A", 7}, {"C", 8}, {"D", 2}, {"G", 5}});
    addEdges("F", {{"D", 2}, {"G", 3}});
    addEdges("G", {{"E", 5}, {"D", 10}, {"F", 3}});
}

void GraphBuilder::addEdges(string sourceName, vector<pair<string, int>> names) {
    Vertex* source = &constructed->vertexes[sourceName];

    for (int i = 0; i < names.size(); ++i)
        source->neighborhood.push_back(new Edge(source, &constructed->vertexes[names[i].first], names[i].second));
}

void GraphBuilder::addVertex(string name) {
    // pair<string, Vertex> pr(name, Vertex(name));
    constructed->vertexes.emplace(string(name), Vertex(name));
}

GraphBuilder::GraphBuilder(size_t graphSize) {
    constructed = new Graph(graphSize);
}

Graph* GraphBuilder::getResult() {
    return constructed;
}

GraphBuilder::GraphBuilder(size_t graphSize, int minWeight, int maxWeight) {
    constructed = new Graph(graphSize);
    this->minWeight = minWeight;
    this->maxWeight = maxWeight;
}
