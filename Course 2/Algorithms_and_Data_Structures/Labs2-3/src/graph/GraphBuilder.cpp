#include <assert.h>
#include "GraphBuilder.h"

void GraphBuilder::generateRandomDirectedGraph(size_t vertexCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight) {
    delete constructed;
    constructed = new Graph(vertexCount);

    // You shall not pass, bitch
    assert(minEdgeWeight < maxEdgeWeight);
    assert(vertexCount <= edgesCount);

    addVertex(0);

    for (size_t i = 0; i < vertexCount-1; ++i) {
        Vertex* randomVertex = constructed->getRandomVertex();

        addVertex(i);
        addEdge(randomVertex->id, i, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }

    for (size_t i = vertexCount; i < edgesCount; i++) {
        Vertex* v1 = constructed->getRandomVertex();
        Vertex* v2 = constructed->getRandomVertex();

        addEdge(v1->id, v2->id, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }
}
void GraphBuilder::generateRandomUndirectedGraph(size_t vertexCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight) {
    delete constructed;
    constructed = new Graph(vertexCount);

    // You shall not pass, bitch
    assert(minEdgeWeight < maxEdgeWeight);
    assert(vertexCount <= edgesCount);

    addVertex(0);

    for (size_t i = 0; i < vertexCount-1; ++i) {
        Vertex* randomVertex = constructed->getRandomVertex();

        addVertex(i);
        addUndirectedEdge(randomVertex->id, i, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }

    for (size_t i = vertexCount; i < edgesCount; i++) {
        Vertex* v1 = constructed->getRandomVertex();
        Vertex* v2 = constructed->getRandomVertex();

        addUndirectedEdge(v1->id, v2->id, minEdgeWeight + rand() % (maxEdgeWeight - minEdgeWeight));
    }
}
void GraphBuilder::generateDijkstraTestGraph() {
    delete constructed;
    constructed = new Graph(7);

    addVertex(0); // start
    addVertex(1);
    addVertex(2);
    addVertex(3);
    addVertex(4);
    addVertex(5); // destination
    addVertex(6);

    /*
    addEdges(0, {{1, 4}, {2, 3}, {4, 7}});
    addEdges(1, {{0, 4}, {2, 6}, {3, 5}});
    addEdges(2, {{0, 3}, {1, 6}, {3, 11}, {4, 8}});
    addEdges(3, {{1, 5}, {2, 11}, {4, 2}, {6, 10}, {5, 2}});
    addEdges(4, {{0, 7}, {2, 8}, {3, 2}, {6, 5}});
    addEdges(5, {{3, 2}, {6, 3}});
    addEdges(6, {{4, 5}, {3, 10}, {5, 3}});
     */
}
void GraphBuilder::generateBellmanFordTestGraph() {
    delete constructed;
    constructed = new Graph(6);

    addVertex(0);
    addVertex(1);
    addVertex(2);
    addVertex(3);
    addVertex(4);
    addVertex(5); // S - start

    /*
    addEdges(0, {{2, 2}});
    addEdges(1, {{0, 1}});
    addEdges(2, {{1, -2}});
    addEdges(3, {{2, -1}, {0, -4}});
    addEdges(4, {{3, 1}});
    addEdges("S", {{0, 10}, {4, 8}});
     */
}
void GraphBuilder::generatePrimTestGraph() {
    delete constructed;
    constructed = new Graph(6);

    addVertex(0); // start
    addVertex(1);
    addVertex(2);
    addVertex(3);
    addVertex(4);
    addVertex(5); // destination

    /*
    addEdges(0, {{1, 2}, {3, 5}, {5, 6}});
    addEdges(1, {{0, 2}, {2, 8}, {3, 6}});
    addEdges(2, {{1, 8}, {3, 3}, {4, 5}});
    addEdges(3, {{0, 5}, {1, 6}, {2, 3}, {4, 6}, {5, 7}});
    addEdges(4, {{2, 5}, {3, 6}, {5, 2}});
    addEdges(5, {{0, 6}, {3, 7}, {4, 2}});
     */
}
void GraphBuilder::generateKruskalTestGraph() {
    delete constructed;
    constructed = new Graph(7);

    addVertex(0); // start
    addVertex(1);
    addVertex(2);
    addVertex(3);
    addVertex(4);
    addVertex(5);
    addVertex(6); // destination

    /*
    addEdges(0, {{1, 2}, {2, 3}, {3, 3}});
    addEdges(1, {{0, 2}, {2, 4}, {4, 3}});
    addEdges(2, {{0, 3}, {1, 4}, {3, 5}, {4, 1}});
    addEdges(3, {{0, 3}, {2, 5}, {5, 7}});
    addEdges(4, {{1, 3}, {2, 1}, {5, 8}});
    addEdges(5, {{3, 7}, {4, 8}, {6, 9}});
    addEdges(6, {{5, 9}});
     */
}

void GraphBuilder::addEdge(int sourceId, int destinationId, int weight) {
    Vertex* source = &constructed->vertexes[sourceId];
    Vertex* destination = &constructed->vertexes[destinationId];
    vector<Vertex*> vertexes = constructed->getAllVertexes();

    source->neighborhood.push_back(new Edge(source, destination, weight));
}
void GraphBuilder::addVertex(int id) {
    // pair<string, Vertex> pr(name, Vertex(name));
    constructed->vertexes.push_back(Vertex(id));
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
void GraphBuilder::addUndirectedEdge(int firstId, int secondId, int weight) {
    this->addEdge(firstId, secondId, weight);
    this->addEdge(firstId, secondId, weight);
}

