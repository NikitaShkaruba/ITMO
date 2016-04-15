#include <limits.h>
#include <iostream>
#include <assert.h>
#include "../graph/Graph.h"
#include "../graph/GraphBuilder.h"

using namespace std;

// Lab 2
list<Vertex*> recoverShortestPath(vector<Vertex*> shortestPaths, Vertex* first, Vertex* last) {
    list<Vertex*> result;

    result.push_back(last);
    Vertex* i = last;
    do {
        i = shortestPaths[i->id];
        if (i == nullptr)
            return list<Vertex*>();

        result.push_back(i);
    } while (i != first);

    result.reverse();
    return result;
}
size_t getMinDistanceIndex(vector<int> &distances, vector<bool> &marked) {
    int min = INT_MAX;
    ssize_t minIndex = -1;

    for (int i = 0; i < distances.size(); i++) {
        if (!marked[i] && distances[i] <= min) {
            min = distances[i];
            minIndex = i;
        }
    }

    assert(minIndex >= 0);
    return (size_t)minIndex;
}
list<Vertex*> Dijkstra(Graph* graph, size_t startId, size_t destinationId) {
    vector<Vertex*> vertices = graph->getAllVertices();

    // Preparations
    vector<int> distances(graph->getVerticesAmount(), INT_MAX);
    vector<bool> marked(graph->getVerticesAmount(), false);
    vector<Vertex*> shortestPreviouses(graph->getVerticesAmount(), nullptr);
    distances[startId] = 0;

    // Find shortest path for all vertices
    for (size_t count = 0; count < vertices.size() - 1; count++) {
        int minIndex = getMinDistanceIndex(distances, marked);
        marked[minIndex] = true;

        if (minIndex == destinationId)
            break;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (list<Edge*>::iterator edgeIt = vertices[minIndex]->neighborhood.begin(); edgeIt != vertices[minIndex]->neighborhood.end(); edgeIt++) {
            if (!marked[(*edgeIt)->destination->id] && distances[minIndex] + (*edgeIt)->weight < distances[(*edgeIt)->destination->id]) {
                distances[(*edgeIt)->destination->id] = distances[minIndex] + (*edgeIt)->weight;
                shortestPreviouses[(*edgeIt)->destination->id] = (*edgeIt)->source;
            }
        }
    }

    return recoverShortestPath(shortestPreviouses, vertices[startId], vertices[destinationId]);
}
list<Vertex*> BellmanFord(Graph* graph, size_t startId, size_t destinationId) {
    vector<Vertex*> vertices = graph->getAllVertices();
    bool isDistancesUpdated = false;

    // Preparation
    vector<int> distances(graph->getVerticesAmount(), INT_MAX);
    vector<Vertex*> shortestPreviouses(graph->getVerticesAmount(), nullptr);
    distances[startId] = 0;

    for(size_t i = 0; i < vertices.size() - 1; i++) {
        for(vector<Vertex*>::iterator vertexIt = vertices.begin(); vertexIt != vertices.end(); vertexIt++) {
            if (distances[(*vertexIt)->id] == INT_MAX) { // int overflow may screw comparison up
                continue;
            } else {
                for (list<Edge *>::iterator neighborhoodIt = (*vertexIt)->neighborhood.begin(); neighborhoodIt != (*vertexIt)->neighborhood.end(); neighborhoodIt++) {
                    if (distances[(*neighborhoodIt)->destination->id] > distances[(*neighborhoodIt)->source->id] + (*neighborhoodIt)->weight) {
                        isDistancesUpdated = true;
                        distances[(*neighborhoodIt)->destination->id] = distances[(*neighborhoodIt)->source->id] + (*neighborhoodIt)->weight;
                        shortestPreviouses[(*neighborhoodIt)->destination->id] = (*neighborhoodIt)->source;
                    }
                }

            }
        }

        if (isDistancesUpdated == false)
            goto AllMinimumPathsHaveFoundLabel;
        else
            isDistancesUpdated = false;
    }

    AllMinimumPathsHaveFoundLabel:
    return recoverShortestPath(shortestPreviouses, vertices[startId], vertices[destinationId]);
}

// Lab 3
bool contains(vector<Vertex*> vertices, size_t id) {
    for (vector<Vertex*>::iterator it = vertices.begin(); it != vertices.end(); it++)
        if ((*it) != nullptr && (*it)->id == id)
            return true;

    return false;
}
Graph* Prim(Graph* graph) {
    GraphBuilder builder(graph->getVerticesAmount());
    vector<Vertex*> vertices = graph->getAllVertices();
    multiset<Edge> allAvailableEdges;

    // preparations
    int startId = 0; //rand() % vertices.size();
    builder.addVertex(startId);
    for(list<Edge*>::iterator startEdgesIt = vertices[startId]->neighborhood.begin(); startEdgesIt != vertices[startId]->neighborhood.end(); startEdgesIt++ )
        allAvailableEdges.insert(**startEdgesIt);

    while(builder.getResult()->getVerticesAmount() != graph->getVerticesAmount() && !allAvailableEdges.empty()) {
        vector<Vertex*> currentVertices = builder.getResult()->getAllVertices();
        multiset<Edge>::iterator lightweight = allAvailableEdges.begin();

        if (!contains(currentVertices, lightweight->destination->id)) {
            builder.addVertex(lightweight->destination->id);
            for(list<Edge*>::iterator neighboursIt = lightweight->destination->neighborhood.begin(); neighboursIt != lightweight->destination->neighborhood.end(); neighboursIt++ ) {
                if (!(*neighboursIt)->isOpposite(*lightweight))
                    allAvailableEdges.insert(**neighboursIt);
            }

            builder.addUndirectedEdge(lightweight->source->id, lightweight->destination->id, lightweight->weight);
        }

        allAvailableEdges.erase(lightweight);
    }

    return builder.getResult();
}
Graph* Kruskal(Graph* graph) {
    GraphBuilder builder(graph->getVerticesAmount());

    GraphBuilder preparator(graph);
    preparator.removeLoops();
    preparator.removeDoubles();

    multiset<Edge> allEdges;
    vector<Vertex*> vertices = graph->getAllVertices();
    for(vector<Vertex*>::iterator vIt = vertices.begin(); vIt != vertices.end(); vIt++)
        for(list<Edge*>::iterator eIt = (*vIt)->neighborhood.begin(); eIt != (*vIt)->neighborhood.end(); eIt++)
            allEdges.insert(**eIt);

    // Now add vertices and edge between them from left to right of edge list if they add new vertices
    while(builder.getResult()->getVerticesAmount() != graph->getVerticesAmount() && !allEdges.empty()) {
        Graph* constructedGraph = builder.getResult();
        multiset<Edge>::iterator min = allEdges.begin();

        if (!constructedGraph->haveCycle(*min)) {
            Graph* currentGraph = builder.getResult();

            if (currentGraph->getVertex(min->source->id) == nullptr)
                builder.addVertex(min->source->id);
            if (currentGraph->getVertex(min->destination->id) == nullptr)
                builder.addVertex(min->destination->id);

            builder.addUndirectedEdge(min->source->id, min->destination->id, min->weight);
        }

        // remove his opposite too;
        allEdges.erase(min);
        for(multiset<Edge>::iterator it = allEdges.begin(); it != allEdges.end(); it++)
            if (it->isOpposite(*min)) {
                allEdges.erase(it);
                break;
            }
    }

    return builder.getResult();
}

