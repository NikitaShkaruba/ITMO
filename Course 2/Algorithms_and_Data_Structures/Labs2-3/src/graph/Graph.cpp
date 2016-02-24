#include "Graph.h"

Vertex* Graph::getVertex(string content) {
    return &vertexes[content];
}

Graph::Graph(size_t vertexCount) {

}

map<string, Vertex*> Graph::getAllVertexes() {
    map<string, Vertex*> result;

    for (map<string, Vertex>::iterator it = vertexes.begin(); it != vertexes.end(); it++)
        result.insert(pair<string, Vertex*>(it->first, &it->second));

    return result;
}

size_t Graph::getVertexAmount() {
    return vertexes.size();
}

size_t Graph::getEdgesAmount() {
    return edgesCount;
}
