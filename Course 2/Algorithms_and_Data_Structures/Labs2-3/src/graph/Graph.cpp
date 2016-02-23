#include "Graph.h"

Vertex* Graph::getVertex(string content) {
    return &vertexes[content];
}

Graph::Graph(size_t vertexCount) {

}
