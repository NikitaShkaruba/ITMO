#include "GraphBuilder.h"

GraphBuilder::GraphBuilder(size_t graphSize) {
    constructed = new Graph(graphSize);
}
GraphBuilder::GraphBuilder(Graph *graph) {
    constructed = graph;
}

void GraphBuilder::generateTestWeb() {
    delete constructed;
    constructed = new Graph(7);

    addVertex(0);   // A
    addVertex(1);   // B
    addVertex(2);   // C
    addVertex(3);   // D
    addVertex(4);   // E
    addVertex(5);   // F

    // TODO: add throwughputs
    addEdges(0, {{1, 9}, {2, 8}});
    addEdges(1, {{3, 6}, {4, 3}});
    addEdges(2, {{4, 4}});
    addEdges(3, {{5, 10}});
    addEdges(4, {{3, 4}, {5, 7}});
}

void GraphBuilder::addVertex(size_t id) {
    constructed->vertices[id] = new Vertex(id);
    constructed->verticesCount++;
}
void GraphBuilder::addEdge(size_t sourceId, size_t destinationId, int weight) {
    Vertex* source = constructed->vertices[sourceId];
    Vertex* destination = constructed->vertices[destinationId];

    source->neighborhood.push_back(new Edge(source, destination, weight));
    constructed->edgesCount++;
}
void GraphBuilder::addUndirectedEdge(size_t firstId, size_t secondId, int weight) {
    this->addEdge(firstId, secondId, weight);
    this->addEdge(secondId, firstId, weight);
}

Graph* GraphBuilder::getResult() {
    return constructed;
}

void GraphBuilder::addEdges(size_t sourceId, vector<pair<size_t, int>> ids) {
    for(vector<pair<size_t, int>>::iterator it = ids.begin(); it != ids.end(); it++)
        addEdge(sourceId, it->first, it->second);
}

void GraphBuilder::copyGraph(Graph& graph) {
    this->constructed = new Graph(graph.getVerticesAmount());

    for(vector<Vertex*>::iterator vIt = constructed->vertices.begin(); vIt != constructed->vertices.end(); vIt++) {
        addVertex((*vIt)->id);
        for(list<Edge*>::iterator eIt = (*vIt)->neighborhood.begin(); eIt != (*vIt)->neighborhood.end(); eIt++) {
            addEdge((*eIt)->source->id, (*eIt)->destination->id, (*eIt)->throughput);
        }
    }
}

void GraphBuilder::removeEdge(Edge *edge) {
    edge->source->neighborhood.remove(edge);
}

Edge *GraphBuilder::getOppositeEdge(Edge *edge) {
    for (list<Edge *>::iterator i = edge->destination->neighborhood.begin(); i != edge->destination->neighborhood.end(); i++) {
        if (*i == edge)
            return *i;
    }

    return nullptr;
}
