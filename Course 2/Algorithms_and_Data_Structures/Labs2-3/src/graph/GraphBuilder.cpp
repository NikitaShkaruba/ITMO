#include "GraphBuilder.h"
#include <assert.h>

GraphBuilder::GraphBuilder(size_t graphSize) {
    constructed = new Graph(graphSize);
}
GraphBuilder::GraphBuilder(Graph *graph) {
    constructed = graph;
}

// TODO: make this method static
void GraphBuilder::generateRandomDirectedGraph(size_t verticesCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight) {
    srand(time(nullptr));

    delete constructed;
    constructed = new Graph(verticesCount);

    for (size_t i = 0; i < verticesCount; ++i)
        addVertex(i);

    for (size_t i = 0; i < edgesCount; i++) {
        Vertex* v1 = constructed->getRandomVertex();
        Vertex* v2 = constructed->getRandomVertex();

        addEdge(v1->id, v2->id, minEdgeWeight + rand() % (minEdgeWeight != maxEdgeWeight? maxEdgeWeight - minEdgeWeight : minEdgeWeight));
    }
}
void GraphBuilder::generateRandomUndirectedGraph(size_t verticesCount, size_t edgesCount, int minEdgeWeight, int maxEdgeWeight) {
    srand(time(nullptr));

    delete constructed;
    constructed = new Graph(verticesCount);

    for (size_t i = 0; i < verticesCount; ++i)
        addVertex(i);

    for (size_t i = 0; i < edgesCount; i++) {
        Vertex* v1 = constructed->getRandomVertex();
        Vertex* v2 = constructed->getRandomVertex();

        addUndirectedEdge(v1->id, v2->id, minEdgeWeight + rand() % (minEdgeWeight != maxEdgeWeight? maxEdgeWeight - minEdgeWeight : minEdgeWeight));
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

    addEdges(0, {{1, 4}, {2, 3}, {4, 7}});
    addEdges(1, {{0, 4}, {2, 6}, {3, 5}});
    addEdges(2, {{0, 3}, {1, 6}, {3, 11}, {4, 8}});
    addEdges(3, {{1, 5}, {2, 11}, {4, 2}, {6, 10}, {5, 2}});
    addEdges(4, {{0, 7}, {2, 8}, {3, 2}, {6, 5}});
    addEdges(5, {{3, 2}, {6, 3}});
    addEdges(6, {{4, 5}, {3, 10}, {5, 3}});
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

    addEdges(0, {{2, 2}});
    addEdges(1, {{0, 1}});
    addEdges(2, {{1, -2}});
    addEdges(3, {{2, -1}, {0, -4}});
    addEdges(4, {{3, 1}});
    addEdges(5, {{0, 10}, {4, 8}});
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

    addEdges(0, {{1, 2}, {3, 5}, {5, 6}});
    addEdges(1, {{0, 2}, {2, 8}, {3, 6}});
    addEdges(2, {{1, 8}, {3, 3}, {4, 5}});
    addEdges(3, {{0, 5}, {1, 6}, {2, 3}, {4, 6}, {5, 7}});
    addEdges(4, {{2, 5}, {3, 6}, {5, 2}});
    addEdges(5, {{0, 6}, {3, 7}, {4, 2}});
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

    addEdges(0, {{1, 2}, {2, 3}, {3, 3}, {0, 0}, {0, 0}});
    addEdges(1, {{0, 2}, {2, 4}, {4, 3}});
    addEdges(2, {{0, 3}, {1, 4}, {3, 5}, {4, 1}, {4, 1}});
    addEdges(3, {{0, 3}, {2, 5}, {5, 7}});
    addEdges(4, {{1, 3}, {2, 1}, {5, 8}});
    addEdges(5, {{3, 7}, {4, 8}, {6, 9}});
    addEdges(6, {{5, 9}});
}

void GraphBuilder::addVertex(size_t id) {
    // pair<string, Vertex> pr(name, Vertex(name));
    constructed->vertices[id] = new Vertex(id);
    constructed->verticesCount++;
}
void GraphBuilder::addEdge(size_t sourceId, size_t destinationId, int weight) {
    Vertex* source = constructed->vertices[sourceId];
    Vertex* destination = constructed->vertices[destinationId];
    vector<Vertex*> vertexes = constructed->getAllVertices();

    source->neighborhood.push_back(new Edge(source, destination, weight));
    constructed->edgesCount++;
}
void GraphBuilder::addUndirectedEdge(size_t firstId, size_t secondId, int weight) {
    this->addEdge(firstId, secondId, weight);
    this->addEdge(secondId, firstId, weight);
}
void GraphBuilder::removeLoops() {
    vector<Vertex*> vertexes = constructed->getAllVertices(); // i nee this for iterator comparison

    for(vector<Vertex*>::iterator vIt = vertexes.begin(); vIt != vertexes.end(); vIt++) {
        for(list<Edge*>::iterator eIt = (*vIt)->neighborhood.begin(); eIt != (*vIt)->neighborhood.end();){
            if ((*eIt)->source == (*eIt)->destination) {
                (*vIt)->neighborhood.erase((eIt++));
                constructed->edgesCount--;
            } else {
                ++eIt;
            }
        }
    }
}
void GraphBuilder::removeDoubles() {
    vector<Vertex*> vertexes = constructed->getAllVertices(); // i need this because of iterator comparison

    for(vector<Vertex*>::iterator vIt = vertexes.begin(); vIt != vertexes.end(); vIt++) {
        for(list<Edge*>::iterator eIt1 = (*vIt)->neighborhood.begin(); eIt1 != (*vIt)->neighborhood.end(); eIt1++) {
            bool isFirst = true;

            (*vIt)->neighborhood.remove_if([&isFirst, eIt1, this](Edge* const e) -> bool {
                if (e->equals(**eIt1)) {
                    if (isFirst) {
                        isFirst = false;
                        return false;
                    } else {
                        constructed->edgesCount--;
                        return true;
                    }
                } else
                    return false;
            });
        }
    }
}

Graph* GraphBuilder::getResult() {
    return constructed;
}

void GraphBuilder::addEdges(size_t sourceId, vector<pair<size_t, int>> ids) {
    for(vector<pair<size_t, int>>::iterator it = ids.begin(); it != ids.end(); it++)
        addEdge(sourceId, it->first, it->second);
}
