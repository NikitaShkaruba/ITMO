#include <list>
#include <limits.h>
#include <assert.h>
#include "../graph/Graph.h"

using namespace std;

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
        for (list<Edge*>::iterator edge = minVertex->neighborhood.begin(); edge != minVertex->neighborhood.end(); edge++) {
            if (!marked[(*edge)->destination] && distances[minVertex] + (*edge)->weight < distances[(*edge)->destination]) {
                distances[(*edge)->destination] = distances[minVertex] + (*edge)->weight;
                shortestPreviouses[(*edge)->destination] = (*edge)->source;
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
