#include <limits.h>
#include <iostream>
#include <assert.h>
#include <cmath>
#include "../graph/Graph.h"
#include "../graph/GraphBuilder.h"
#include "algorithms.h"

using namespace std;

void recursion(Vertex *chainHead, vector<list<Edge *>> &increaseChains, list<Edge *> &currentChain, Vertex *sink) {
    for (list<Edge *>::iterator i = chainHead->neighborhood.begin(); i != chainHead->neighborhood.end() ; i++) {
        if ((*i)->destination != sink) {
            currentChain.push_back((*i));
            recursion((*i)->destination, increaseChains, currentChain, sink);
            currentChain.pop_back();
        } else {
            currentChain.push_back((*i));
            increaseChains.push_back(currentChain);
            currentChain.pop_back();
        }
    }
}

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
vector<list<Edge*>> getIncreaseChains(Graph* g, Vertex* source, Vertex* sink) {
    vector<list<Edge*>> increaseChains;
    list<Edge*> currentChain;

    recursion(source, increaseChains, currentChain, sink);
    return increaseChains;
}
map<Edge*, int> calculateFlow(Graph* graph, Vertex* source, Vertex* sink) {
    map<Edge*, int> flow;
    vector<list<Edge*>> increaseChains = getIncreaseChains(graph, source, sink);

    for(vector<list<Edge*>>::iterator incIt = increaseChains.begin(); incIt != increaseChains.end(); incIt++) {
        int minDifference = getMinDifference(*incIt, flow);

        for (list<Edge*>::iterator edgeIt = incIt->begin(); edgeIt != incIt->end(); edgeIt++) {
            flow[*edgeIt] = flow[*edgeIt] + minDifference;
        }
    }

    return flow;
}
