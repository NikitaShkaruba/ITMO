#include <iostream>
#include "Graph.h"

Vertex *Graph::getRandomVertex() {
    vector<Vertex*>::iterator  it;

    do {
        it = vertices.begin();
        std::advance(it, rand() % vertices.size());
    } while (*it == nullptr);

    return *it;
}
Vertex* Graph::getVertex(int id) {
    return vertices[id];
}
vector<Vertex*> Graph::getAllVertices() {
    vector<Vertex*> result;

    for (auto it = vertices.begin(); it != vertices.end(); it++)
        if (*it != nullptr)
            result.push_back(*it);

    return result;
}

size_t Graph::getVerticesAmount() {
    return verticesCount;
}
size_t Graph::getEdgesAmount() {
    // TODO: remove this plug, add directional\undirectional logic
    return edgesCount;
}

bool Graph::haveCycle(Edge edge) {
    bool marked[vertices.capacity()];
    for (int i = 0; i < vertices.capacity(); ++i)
        marked[i] = false;

    DepthFirstSearch(marked, edge.destination->id);

    return marked[edge.source->id];
}

Graph::Graph(size_t verticesAmount) {
    // It is reserved because of one-to-one relation between id and vector index.
    vertices.reserve(verticesAmount);
    for (int i = 0; i < verticesAmount; ++i) {
        vertices.push_back(nullptr);
    }

    this->edgesCount = 0;
    this->verticesCount = 0;
}

void Graph::DepthFirstSearch(bool marked[], int currentIndex) {
    marked[currentIndex] = true;

    if (vertices[currentIndex] != nullptr) {
        for (list<Edge *>::iterator eIt = vertices[currentIndex]->neighborhood.begin(); eIt != vertices[currentIndex]->neighborhood.end(); eIt++) {
            if (!marked[(*eIt)->destination->id]) {
                DepthFirstSearch(marked, (*eIt)->destination->id);
            }
        }
    }
}


