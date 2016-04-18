#pragma once

#include "../graph/Graph.h"

using namespace std;

int getMaxFlow(map<Edge*, int> flow, Vertex* source);
vector<list<Edge*>> getIncreaseChains(Graph* g, Vertex* source, Vertex* sink);
map<Edge*, int> calculateFlow(Graph* graph, Vertex* source, Vertex* sink);


