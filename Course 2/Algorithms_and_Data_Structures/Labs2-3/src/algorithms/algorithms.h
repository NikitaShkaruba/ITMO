#pragma once

#include "../graph/Graph.h"

using namespace std;

list<Vertex*> Dijkstra(Graph* graph, int startId, int destinationId);
list<Vertex*> BellmanFord(Graph* graph, int startId, int destinationId);

Graph* Prim(Graph* graph);
Graph* Kruskal(Graph* graph);

