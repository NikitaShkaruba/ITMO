#include <limits.h>
#include <iostream>
#include <assert.h>
#include <cmath>
#include "../graph/Graph.h"
#include "../graph/GraphBuilder.h"
#include "algorithms.h"

using namespace std;

int getMaxFlow(map<Edge*, int> flow, Vertex* source) {
    int maxFlow = 0;

    for (list<Edge*>::iterator i = source->neighborhood.begin(); i != source->neighborhood.end(); i++)
        maxFlow += flow[*i];

    return maxFlow;
}
int getMinDifference(list<Edge*> chain, map<Edge*, int> flow) {
    int min = INT_MAX;
    for(list<Edge*>::iterator edgeIt = chain.begin(); edgeIt != chain.end(); edgeIt++)
        if ((*edgeIt)->throughput - flow[*edgeIt] < min)
            min = (*edgeIt)->throughput - flow[*edgeIt];

    assert(min != INT_MAX);
    return min;
}
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
            if (!marked[(*edgeIt)->destination->id] && distances[minIndex] + (*edgeIt)->throughput < distances[(*edgeIt)->destination->id]) {
                distances[(*edgeIt)->destination->id] = distances[minIndex] + (*edgeIt)->throughput;
                shortestPreviouses[(*edgeIt)->destination->id] = (*edgeIt)->source;
            }
        }
    }

    return recoverShortestPath(shortestPreviouses, vertices[startId], vertices[destinationId]);
}
list<Edge*> getEdgesBetweenVertices(list<Vertex*> vertices) {

}
map<Edge*, int> calculateFlow(Graph* graph, Vertex* source, Vertex* sink) {
    GraphBuilder builder(graph);
    map<Edge*, int> flow;

    while(true) {
        list<Edge*> shortestPath = getEdgesBetweenVertices(Dijkstra(graph, source->id, sink->id));
        int bottleneck = getMinDifference(shortestPath, flow);

        for (list<Edge*>::iterator edge = shortestPath.begin(); edge != shortestPath.end() ; ++edge) {
            // What to do with it?
            flow[*edgeIt] = flow[*edgeIt] + bottleneck;

            if (flow[*edge] + bottleneck == (*edge)->throughput) {
                builder.removeEdge(*edge);
                builder.addEdge((*edge)->destination->id, (*edge)->source->id, (*edge)->throughput);
            } else if (flow[*edge] + bottleneck == 0) {
                assert(false);
            } else {
                Edge* opposite = builder.getOppositeEdge(*edge);
                if (opposite == nullptr) {
                    builder.addEdge((*edge)->destination->id, (*edge)->source->id, (*edge)->throughput);
                    builder.getOppositeEdge(*edge)->throughput = flow[*edge] = flow[*edge] + bottleneck;
                    (*edge)->throughput =
                    opposite->throughput =
                }

            }

        }


        for (list<Edge*>::iterator edgeIt = increaseChains.begin(); edgeIt != increaseChains.end(); edgeIt++)
    }

    return flow;
}
