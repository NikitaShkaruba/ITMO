#include <iostream>
#include "Graph.h"

Graph::Graph(size_t verticesAmount) : vertices(verticesAmount, nullptr) {
    // vertices are reserved because of encapsulation(inner realization)

    this->edgesCount = 0;
    this->verticesCount = 0;
}

Vertex *Graph::getRandomVertex() {
    vector<Vertex*>::iterator  it;

    do {
        it = vertices.begin();
        it += rand() % verticesCount;
    } while (*it == nullptr);

    return *it;
}
Vertex* Graph::getVertex(size_t id) {
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
    for (size_t i = 0; i < vertices.capacity(); ++i)
        marked[i] = false;

    DepthFirstSearch(marked, edge.destination->id);

    return marked[edge.source->id];
}

void Graph::DepthFirstSearch(bool marked[], size_t currentIndex) {
    marked[currentIndex] = true;

    if (vertices[currentIndex] != nullptr) {
        for (list<Edge *>::iterator eIt = vertices[currentIndex]->neighborhood.begin(); eIt != vertices[currentIndex]->neighborhood.end(); eIt++) {
            if (!marked[(*eIt)->destination->id]) {
                DepthFirstSearch(marked, (*eIt)->destination->id);
            }
        }
    }
}

vector<Edge*> Graph::getAllEdges() {
    vector<Edge*> result;

    for (vector<Vertex*>::iterator vIt = vertices.begin(); vIt != vertices.end(); vIt++)
        for(list<Edge*>::iterator eIt = (*vIt)->neighborhood.begin(); eIt != (*vIt)->neighborhood.end(); eIt++)
            result.push_back(*eIt);

    return result;
}
