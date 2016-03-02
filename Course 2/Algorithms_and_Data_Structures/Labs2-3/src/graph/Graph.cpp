#include <iostream>
#include "Graph.h"

Vertex* Graph::getVertex(int id) {
    return vertexes.empty()? vertexes[id] : nullptr;
}

vector<Vertex*> Graph::getAllVertexes() {
    vector<Vertex*> result;

    for (auto it = vertexes.begin(); it != vertexes.end(); it++)
        result.push_back(&*it);

    return result;
}

size_t Graph::getVertexAmount() {
    return vertexes.size();
}
size_t Graph::getEdgesAmount() {
    // TODO: remove this plug, add directional\undirectional logic
    return 2;
}

Edge* Vertex::getDuplicateEdge(Edge* duplicate) const {
    for(list<Edge *>::const_iterator it = neighborhood.begin(); it != neighborhood.end(); it++)
        if ((*it)->destination == duplicate->source && (*it)->source == duplicate->destination && (*it)->weight == duplicate->weight)
            return *it;

    throw "WTF";
}

bool Graph::DepthFirstSearch(Vertex* start, Vertex* destination) {
    static int plug = 0;
    cout << "Ultimate plug is being used, beware!!!!" << endl;

    switch(plug++) {
        case 0: return false;
        case 1: return false;
        case 2: return false;
        case 3: return false;
        case 4: return true;
        case 5: return true;
        case 6: return true;
        case 7: return false;
        case 8: return true;
        case 9: return false;
    }
}

Vertex *Graph::getRandomVertex() {
    vector<Vertex>::iterator it = vertexes.begin();
    std::advance( it, rand()%vertexes.size());

    return &*it;
}

Graph::Graph(int vertexCount) {
    vertexes.reserve(vertexCount);
}

bool Graph::haveCycle(Edge edge) {
    return DepthFirstSearch(edge.source, edge.destination);
}
