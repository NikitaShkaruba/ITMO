#include <assert.h>
#include "GraphBuilder.h"

void GraphBuilder::generateRandomDirectedGraph(size_t vertexCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight) {
    delete constructed;
    constructed = new Graph(vertexCount);

    // You shall not pass, bitch
    assert(minEdgeWeight < maxEdgeWeight);
    assert(vertexCount <= edgesCount);

    addVertex("v0");

    for (size_t i = 0; i < vertexCount-1; ++i) {
        Vertex* randomVertex = constructed->getRandomVertex();

        string newVertexName = "v" + to_string(i);
        addVertex(newVertexName);
        addEdge(randomVertex->name, newVertexName, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }

    for (size_t i = vertexCount; i < edgesCount; i++) {
        Vertex* v1 = constructed->getRandomVertex();
        Vertex* v2 = constructed->getRandomVertex();

        addEdge(v1->name, v2->name, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }
}
void GraphBuilder::generateRandomUndirectedGraph(size_t vertexCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight) {
    delete constructed;
    constructed = new Graph(vertexCount);

    // You shall not pass, bitch
    assert(minEdgeWeight < maxEdgeWeight);
    assert(vertexCount <= edgesCount);

    addVertex("v0");

    for (size_t i = 0; i < vertexCount-1; ++i) {
        Vertex* randomVertex = constructed->getRandomVertex();

        string newVertexName = "v" + to_string(i);
        addVertex(newVertexName);
        addUndirectedEdge(randomVertex->name, newVertexName, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }

    for (size_t i = vertexCount; i < edgesCount; i++) {
        Vertex* v1 = constructed->getRandomVertex();
        Vertex* v2 = constructed->getRandomVertex();

        addUndirectedEdge(v1->name, v2->name, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }
}
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
void GraphBuilder::generateKruskalTestGraph() {
    delete constructed;
    constructed = new Graph(7);

    addVertex("A"); // start
    addVertex("B");
    addVertex("C");
    addVertex("D");
    addVertex("E");
    addVertex("F"); // destination
    addVertex("G"); // destination

    addEdges("A", {{"B", 2}, {"C", 3}, {"D", 3}});
    addEdges("B", {{"A", 2}, {"C", 4}, {"E", 3}});
    addEdges("C", {{"A", 3}, {"B", 4}, {"D", 5}, {"E", 1}});
    addEdges("D", {{"A", 3}, {"C", 5}, {"F", 7}});
    addEdges("E", {{"B", 3}, {"C", 1}, {"F", 8}});
    addEdges("F", {{"D", 7}, {"E", 8}, {"G", 9}});
    addEdges("G", {{"F", 9}});
}

void GraphBuilder::addEdge(string sourceName, string destinationName, int weight) {
    Vertex* source = &constructed->vertexes[sourceName];
    Vertex* destination = &constructed->vertexes[destinationName];
    map<string, Vertex*> vertexes = constructed->getAllVertexes();

    source->neighborhood.push_back(new Edge(source, destination, weight));
}
void GraphBuilder::addEdges(string sourceName, vector<pair<string, int>> names) {
    Vertex* source = &constructed->vertexes[sourceName];
    map<string, Vertex*> vertexes = constructed->getAllVertexes();

    for (int i = 0; i < names.size(); ++i)
        addEdge(sourceName, names[i].first, names[i].second);
}
void GraphBuilder::addVertex(string name) {
    // pair<string, Vertex> pr(name, Vertex(name));
    constructed->vertexes.emplace(string(name), Vertex(name));
}
Graph* GraphBuilder::getResult() {
    return constructed;
}

GraphBuilder::GraphBuilder(size_t graphSize) {
    constructed = new Graph(graphSize);
}
size_t GraphBuilder::getCurrentGraphVertexesAmount() {
    return constructed->vertexes.size();
}
void GraphBuilder::addUndirectedEdge(string vertexName1, string vertexName2, int weight) {
    this->addEdge(vertexName1, vertexName2, weight);
    this->addEdge(vertexName2, vertexName1, weight);
}

