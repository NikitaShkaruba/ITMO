#include "GraphBuilder.h"

GraphBuilder::GraphBuilder(size_t graphSize) {
    constructed = new Graph(graphSize);
}
GraphBuilder::GraphBuilder(Graph *graph) {
    constructed = graph;
}

void GraphBuilder::generateComputerNetwork1() {
    delete constructed;
    constructed = new Graph(5);

    addVertex(0, 100);
    addVertex(1, 2);
    addVertex(2, 1);
    addVertex(3, 3);
    addVertex(4, 10);

    addEdge(0, 2, 0);
    addEdge(2, 1, 0);
    addEdge(3, 2, 0);
    addEdge(3, 4, 0);
    addEdge(4, 3, 0);
}

void GraphBuilder::generateComputerNetwork2() {
    delete constructed;
    constructed = new Graph(10);

    addVertex(0, 419);
    addVertex(1, 467);
    addVertex(2, 334);
    addVertex(3, 500);
    addVertex(4, 869);
    addVertex(5, 724);
    addVertex(6, 478);
    addVertex(7, 358);
    addVertex(8, 962);
    addVertex(9, 464);

    addEdge(1, 0, 0);
    addEdge(0, 2, 0);
    addEdge(2, 3, 0);
    addEdge(2, 8, 0);
    addEdge(3, 0, 0);
    addEdge(8, 2, 0);
    addEdge(8, 0, 0);

    addEdge(4, 7, 0);
    addEdge(7, 9, 0);
    addEdge(7, 6, 0);
    addEdge(9, 6, 0);
    addEdge(6, 5, 0);
    addEdge(5, 4, 0);
}

void GraphBuilder::addVertex(size_t id, int terminalsAmount) {
    constructed->vertices[id] = new Vertex(id, terminalsAmount);
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
void GraphBuilder::addUndirectedEdges(size_t sourceId, vector<pair<size_t, int>> ids) {
    for(vector<pair<size_t, int>>::iterator it = ids.begin(); it != ids.end(); it++) {
        addUndirectedEdge(sourceId, it->first, it->second);
    }
}

void GraphBuilder::copyGraph(Graph& graph) {
    this->constructed = new Graph(graph.getVerticesAmount());

    for(vector<Vertex*>::iterator vIt = constructed->vertices.begin(); vIt != constructed->vertices.end(); vIt++) {
        addVertex((*vIt)->id, (*vIt)->terminalsAmount);
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
