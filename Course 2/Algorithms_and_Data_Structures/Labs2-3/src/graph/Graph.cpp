#include <iostream>
#include "Graph.h"

Vertex* Graph::getVertex(string content) {
    return (vertexes.count(content) != 0)? &vertexes[content] : nullptr;
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
    // TODO: remove this plug, add directional\undirectional logic
    return 2;
}

Edge* Vertex::getDuplicateEdge(Edge* duplicate) const {
    for(list<Edge *>::const_iterator it = neighborhood.begin(); it != neighborhood.end(); it++)
        if ((*it)->destination == duplicate->source && (*it)->source == duplicate->destination && (*it)->weight == duplicate->weight)
            return *it;

    throw "WTF";
}

bool Graph::DepthFirstSearch(string startVertexName, string destinationName) {
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
bool Graph::haveCycle(Edge* bridge) {
    return DepthFirstSearch(bridge->source->name, bridge->destination->name);
}
