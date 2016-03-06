#include <iostream>
#include "Graph.h"

Vertex* Graph::getVertex(int id) {
    return vertexes[id];
}

vector<Vertex*> Graph::getAllVertexes() {
    vector<Vertex*> result;

    for (auto it = vertexes.begin(); it != vertexes.end(); it++)
        if (*it != nullptr)
            result.push_back(*it);

    return result;
}

size_t Graph::getVertexAmount() {
    return vertexesCount;
}
size_t Graph::getEdgesAmount() {
    // TODO: remove this plug, add directional\undirectional logic
    return edgesCount;
}

Edge* Vertex::getDuplicateEdge(Edge* duplicate) const {
    for(list<Edge *>::const_iterator it = neighborhood.begin(); it != neighborhood.end(); it++)
        if ((*it)->destination == duplicate->source && (*it)->source == duplicate->destination && (*it)->weight == duplicate->weight)
            return *it;

    throw "WTF";
}

void Graph::DepthFirstSearch(bool marked[], int currentIndex) {
    marked[currentIndex] = true;

    if (vertexes[currentIndex] != nullptr) {
        for (list<Edge *>::iterator eIt = vertexes[currentIndex]->neighborhood.begin(); eIt != vertexes[currentIndex]->neighborhood.end(); eIt++) {
            if (!marked[(*eIt)->destination->id]) {
                DepthFirstSearch(marked, (*eIt)->destination->id);
            }
        }
    }
}

Vertex *Graph::getRandomVertex() {
    vector<Vertex*>::iterator  it;

    do {
        it = vertexes.begin();
        std::advance(it, rand() % vertexes.size());
    } while (*it == nullptr);

    return *it;
}

Graph::Graph(int vertexCount) {
    vertexes.reserve(vertexCount);
    // reserved for id's
    for (int i = 0; i < vertexCount; ++i) {
        vertexes.push_back(nullptr);
    }

    edgesCount = 0;
    vertexesCount = 0;
}

bool Graph::haveCycle(Edge edge) {
    bool marked[vertexes.capacity()];
    for (int i = 0; i < vertexes.capacity(); ++i)
        marked[i] = false;

    DepthFirstSearch(marked, edge.destination->id);

    return marked[edge.source->id];
}
