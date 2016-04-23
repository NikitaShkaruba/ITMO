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
        if ((*edgeIt)->throughput < min)
            min = (*edgeIt)->throughput;

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
        if (!marked[i] && ((distances[i] <= min && distances[i] != 0) || (i == 0))) {
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
            if ((*edgeIt)->throughput != 0 && (!marked[(*edgeIt)->destination->id] && distances[minIndex] + (*edgeIt)->throughput < distances[(*edgeIt)->destination->id])) {
                distances[(*edgeIt)->destination->id] = distances[minIndex] + (*edgeIt)->throughput;
                shortestPreviouses[(*edgeIt)->destination->id] = (*edgeIt)->source;
            }
        }
    }

    return recoverShortestPath(shortestPreviouses, vertices[startId], vertices[destinationId]);
}
list<Edge*> getEdgesBetweenVertices(list<Vertex*> vertices) {
    list<Edge*> edgePath;

    list<Vertex*>::iterator next = vertices.begin();
    next++;
    for (list<Vertex *>::iterator cur = vertices.begin(); cur != vertices.end(); cur++, next++) {
        for(list<Edge*>::iterator neighbour = (*cur)->neighborhood.begin(); neighbour != (*cur)->neighborhood.end(); neighbour++) {
            if((*neighbour)->destination == *next) {
                edgePath.push_back(*neighbour);
                break;
            }
        }
    }

    return edgePath;
}
Edge* findOppositeEdge(Edge* edge) {
    for (list<Edge *>::iterator i = edge->destination->neighborhood.begin(); i != edge->destination->neighborhood.end(); i++)
        if (edge->isOpposite(**i))
            return *i;

    return nullptr;
}
map<Edge*, int> calculateFlow(Graph* graph, Vertex* source, Vertex* sink) {
    GraphBuilder builder(graph);
    map<Edge*, int> edgesBefore;
    map<Edge*, int> flow;

    // I have to remember edges before, because my algorithm changes their throughputs
    vector<Edge *> allEdges = graph->getAllEdges();
    for(vector<Edge *>::iterator edgeIt = allEdges.begin(); edgeIt != allEdges.end(); edgeIt++)
        edgesBefore.insert(std::pair<Edge*, int>(*edgeIt, (*edgeIt)->throughput));

    list<Vertex*> v = Dijkstra(graph, source->id, sink->id);
    list<Edge*> shortestPath = getEdgesBetweenVertices(v);
    for(; !shortestPath.empty(); shortestPath = getEdgesBetweenVertices(Dijkstra(graph, source->id, sink->id))) {
        int bottleneck = getMinDifference(shortestPath, flow);

        for (list<Edge*>::iterator edge = shortestPath.begin(); edge != shortestPath.end() ; ++edge) {
            flow[*edge] = flow[*edge] + bottleneck;

            Edge* opposite = findOppositeEdge(*edge);

            if ((*edge)->throughput - bottleneck == 0) {                       // edge is filled
                (*edge)->throughput = 0;

                if(opposite == nullptr)
                    builder.addEdge((*edge)->destination->id, (*edge)->source->id, bottleneck);
                else
                    opposite->throughput += bottleneck;
            } else if ((opposite == nullptr && bottleneck == (*edge)->throughput) || (opposite != nullptr && opposite->throughput == 0)) {     // edge is empty
                if (opposite == nullptr)
                    builder.addEdge((*edge)->destination->id, (*edge)->source->id, (*edge)->throughput);
                else
                    opposite->throughput += bottleneck;

                (*edge)->throughput = 0;
            } else {             // normal case, edge is not empty, but not filled
                if (opposite == nullptr)
                    builder.addEdge((*edge)->destination->id, (*edge)->source->id, bottleneck);
                else
                    opposite->throughput += bottleneck;

                (*edge)->throughput -= bottleneck;
            }
        }
    }

    // recover throughputs, delete algorithm-added edges
    allEdges = graph->getAllEdges();
    for(vector<Edge *>::iterator edgeIt = allEdges.begin(); edgeIt != allEdges.end(); edgeIt++) {
        if (edgesBefore.count(*edgeIt) == 0)
            builder.removeEdge(*edgeIt);
        else
            (*edgeIt)->throughput = edgesBefore[*edgeIt];
    }

    return flow;
}
