#include "GraphBuilder.h"

void GraphBuilder::generateDijkstraTestGraph() {
    delete constructed;
    constructed = new Graph(7);

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
void GraphBuilder::generateBellmanFordTestGraph() {
    delete constructed;
    constructed = new Graph(6);

    addVertex("A");
    addVertex("B");
    addVertex("C");
    addVertex("D");
    addVertex("E");
    addVertex("S"); // start

    addEdges("A", {{"C", 2}});
    addEdges("B", {{"A", 1}});
    addEdges("C", {{"B", -2}});
    addEdges("D", {{"C", -1}, {"A", -4}});
    addEdges("E", {{"D", 1}});
    addEdges("S", {{"A", 10}, {"E", 8}});
}
void GraphBuilder::generatePrimTestGraph() {
    delete constructed;
    constructed = new Graph(6);

    addVertex("A"); // start
    addVertex("B");
    addVertex("C");
    addVertex("D");
    addVertex("E");
    addVertex("F"); // destination

    addEdges("A", {{"B", 2}, {"D", 5}, {"F", 6}});
    addEdges("B", {{"A", 2}, {"C", 8}, {"D", 6}});
    addEdges("C", {{"B", 8}, {"D", 3}, {"E", 5}});
    addEdges("D", {{"A", 5}, {"B", 6}, {"C", 3}, {"E", 6}, {"F", 7}});
    addEdges("E", {{"C", 5}, {"D", 6}, {"F", 2}});
    addEdges("F", {{"A", 6}, {"D", 7}, {"E", 2}});
}

void GraphBuilder::tryIncreaseEdgesCount(string sourceName, string destinationName) {
}
void GraphBuilder::addEdge(string sourceName, string destinationName, int weight) {
    Vertex* source = &constructed->vertexes[sourceName];
    Vertex* destination = &constructed->vertexes[destinationName];
    map<string, Vertex*> vertexes = constructed->getAllVertexes();

    source->neighborhood.push_back(new Edge(source, destination, weight));

    // undirected graph - graph with tho different edges(!) in my implementation, and i do need to increae edges count somehow :/
    for (list<Edge*>::iterator it = vertexes[destinationName]->neighborhood.begin(); it != vertexes[destinationName]->neighborhood.end(); it++)
        if ((*it)->destination == vertexes[sourceName])
            return;
    constructed->edgesCount++;
}
void GraphBuilder::addEdges(string sourceName, vector<pair<string, int>> names) {
    Vertex* source = &constructed->vertexes[sourceName];
    map<string, Vertex*> vertexes = constructed->getAllVertexes();

    for (int i = 0; i < names.size(); ++i) {
        source->neighborhood.push_back(new Edge(source, &constructed->vertexes[names[i].first], names[i].second));

        // undirected graph - graph with tho different edges(!) in my implementation, and i do need to increae edges count somehow :/
        for (list<Edge*>::iterator it = vertexes[names.at(i).first]->neighborhood.begin(); it != vertexes[names.at(i).first]->neighborhood.end(); it++)
            if ((*it)->destination == vertexes[sourceName])
                return;
        constructed->edgesCount++;
    }
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

size_t GraphBuilder::getCurrentGraphVertexesAmount() {
    return constructed->vertexes.size();
}

