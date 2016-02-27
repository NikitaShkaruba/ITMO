#include <list>
#include <limits.h>
#include <assert.h>
#include "../graph/Graph.h"
#include "../graph/GraphBuilder.h"

using namespace std;

// Lab 2
list<Vertex*> recoverShortestPath(map<Vertex *, Vertex *> shortestPaths, Vertex* last) {
    list<Vertex*> result;

    result.push_back(last);
    for (Vertex* i = shortestPaths[last]; i != nullptr ; i = shortestPaths[i]) {
        result.push_back(i);
    }

    result.reverse();
    return result;
}

// TODO: refactor is needed
Vertex* getVertexWithMinDistance(map<Vertex*, int> distances, map<Vertex*, bool> marks) {
    int min = INT_MAX;
    Vertex* minVertex = nullptr;

    for (map<Vertex*, int>::iterator it = distances.begin(); it != distances.end(); it++) {
        if (marks[it->first] == false && it->second <= min) {
            min = it->second;
            minVertex = it->first;
        }
    }

    assert(minVertex != nullptr);
    return minVertex;
}
list<Vertex*> Dijkstra(Graph* graph, string startName, string destinationName) {
    map<Vertex*, int> distances;
    map<Vertex*, bool> marked;
    map<string, Vertex*> vertexes = graph->getAllVertexes();
    map<Vertex*, Vertex*> shortestPreviouses;

    // Preparations
    for (map<string, Vertex*>::iterator it = vertexes.begin(); it !=vertexes.end(); it++) {
        distances.insert(pair<Vertex*, int>(it->second, INT_MAX));
        marked.insert(pair<Vertex*,bool>(it->second, false));
    }
    distances[vertexes[startName]] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < vertexes.size()-1; count++) {
        Vertex* minVertex = getVertexWithMinDistance(distances, marked);
        marked[minVertex] = true;

        if (minVertex == vertexes[destinationName])
            break;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (list<Edge*>::iterator edgeIt = minVertex->neighborhood.begin(); edgeIt != minVertex->neighborhood.end(); edgeIt++) {
            if (!marked[(*edgeIt)->destination] && distances[minVertex] + (*edgeIt)->weight < distances[(*edgeIt)->destination]) {
                distances[(*edgeIt)->destination] = distances[minVertex] + (*edgeIt)->weight;
                shortestPreviouses[(*edgeIt)->destination] = (*edgeIt)->source;
            }
        }
    }

    return recoverShortestPath(shortestPreviouses, vertexes[destinationName]);
}

list<Vertex*> BellmanFord(Graph* graph, string startName, string destinationName) {
    map<Vertex*, int> distances;
    map<Vertex*, Vertex*> shortestPreviouses;
    map<string, Vertex*> vertexes = graph->getAllVertexes();

    // Preparation
    for (map<string, Vertex*>::iterator it = vertexes.begin(); it != vertexes.end(); it++)
        distances[it->second] = INT_MAX;
    distances[vertexes[startName]] = 0;

    for(int i = 0; i < vertexes.size()-1; i++) {
        for(map<string, Vertex*>::iterator vertexIt = vertexes.begin(); vertexIt != vertexes.end(); vertexIt++) {
            int s = distances[vertexIt->second];
            if (s == INT_MAX) // int overflow may screw comparison up
                continue;
            else
                for(list<Edge*>::iterator neighborhoodIt = vertexIt->second->neighborhood.begin(); neighborhoodIt != vertexIt->second->neighborhood.end(); neighborhoodIt++) {
                    if (distances[(*neighborhoodIt)->destination] > distances[(*neighborhoodIt)->source] + (*neighborhoodIt)->weight) {
                        distances[(*neighborhoodIt)->destination] = distances[(*neighborhoodIt)->source] + (*neighborhoodIt)->weight;
                        shortestPreviouses[(*neighborhoodIt)->destination] = (*neighborhoodIt)->source;
                    }
                }
        }
    }

    return recoverShortestPath(shortestPreviouses, vertexes[destinationName]);
}

// Lab 3
Edge*getLightweightestEdge(list<Edge *> edges) {
    Edge* min = edges.front();

    for(list<Edge*>::iterator edgeIt = edges.begin(); edgeIt != edges.end(); edgeIt++)
        if ((*edgeIt)->weight < min->weight)
            min = *edgeIt;

    return min;
}
Graph * Prim(Graph* graph, string startName) {
    GraphBuilder builder(graph->getVertexAmount());
    map<string, Vertex*> vertexes = graph->getAllVertexes();
    list<Edge*> allAvailableEdges;

    // preparations
    builder.addVertex(vertexes[startName]->name);
    for(list<Edge*>::iterator edgeIt = vertexes[startName]->neighborhood.begin(); edgeIt != vertexes[startName]->neighborhood.end(); edgeIt++ )
        allAvailableEdges.push_back(*edgeIt);

    while(builder.getCurrentGraphVertexesAmount() != graph->getVertexAmount()) {
        map<string, Vertex*> currentVertexes = builder.getResult()->getAllVertexes();
        Edge* lightweight = getLightweightestEdge(allAvailableEdges);

        if (currentVertexes.count(lightweight->destination->name) == 0) {
            builder.addVertex(lightweight->destination->name);
            for(list<Edge*>::iterator neighboursIt = lightweight->destination->neighborhood.begin(); neighboursIt != lightweight->destination->neighborhood.end(); neighboursIt++ )
                allAvailableEdges.push_back(*neighboursIt);


            builder.addUndirectedEdge(lightweight->source->name, lightweight->destination->name, lightweight->weight);
        }

        allAvailableEdges.remove(lightweight);
        allAvailableEdges.remove(lightweight->destination->getDuplicateEdge(lightweight));
    }

    return builder.getResult();
}

Edge* findMinEdge(list<Edge*> edges) {
    Edge* min = *edges.begin();

    for (list<Edge *>::iterator eIt = edges.begin(); eIt != edges.end(); eIt++)
        if ((*eIt)->weight < min->weight)
            min = (*eIt);

    return min;
}
void removeLoops(list<Edge*>& edges) {
    for(list<Edge*>::iterator eIt = edges.begin(); eIt != edges.end(); eIt++) {
        if ((*eIt)->destination == (*eIt)->source)
            edges.remove(*eIt);
    }
}
void removeDoubles(list<Edge*> &edges) {
    for(list<Edge*>::iterator eIt = edges.begin(); eIt != edges.end(); eIt++) {
        int currentEdgeCount = 0;

        for (list<Edge*>::iterator eIt2 = edges.begin(); eIt2 != edges.end(); eIt2++)
            if ((*eIt)->equals(**eIt2) && ++currentEdgeCount > 2) // 2 because of unordered implementation
                edges.remove(*eIt2);
    }
}
Graph* Kruskal(Graph* graph) {
    GraphBuilder builder(graph->getVertexAmount());
    map<string, Vertex*> vertexes = graph->getAllVertexes();
    list<Edge*> allAvailableEdges;

    // sort it by weight
    for(map<string, Vertex*>::iterator vIt = vertexes.begin(); vIt != vertexes.end(); vIt++) {
        for(list<Edge*>::iterator eIt = (*vIt).second->neighborhood.begin(); eIt != (*vIt).second->neighborhood.end(); eIt++) {
            allAvailableEdges.push_back((*eIt));
        }
    }
    removeLoops(allAvailableEdges);
    removeDoubles(allAvailableEdges);

    // Now add vertisies and edge between them from left to right of edge list if they add new vertices
    while(builder.getCurrentGraphVertexesAmount() != graph->getVertexAmount()) {
        Graph* constructedGraph = builder.getResult();
        Edge* min = findMinEdge(allAvailableEdges);

        if (!constructedGraph->haveCycle(min)) {
            Graph* currentGraph = builder.getResult();

            if (currentGraph->getVertex(min->source->name) == nullptr)
                builder.addVertex(min->source->name);
            if (currentGraph->getVertex(min->destination->name) == nullptr)
                builder.addVertex(min->destination->name);

            builder.addUndirectedEdge(min->source->name, min->destination->name, min->weight);
        }

        allAvailableEdges.remove(min);
        allAvailableEdges.remove(min->destination->getDuplicateEdge(min));

    }

    return builder.getResult();
}
