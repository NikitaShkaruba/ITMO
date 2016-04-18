#include "graph/Graph.h"
#include "graph/GraphBuilder.h"
#include "algorithms/algorithms.h"
#include <iostream>

using namespace std;

void runGetPositiveChainsTest() {
    cout << "Testing positive chains retrieving algorithm" << endl;

    GraphBuilder builder(6);
    builder.generateTestWeb();
    Graph* g = builder.getResult();

    vector<list<Edge*>> increaseChains = getIncreaseChains(g, g->getVertex(0), g->getVertex(5));

    cout << "Positive edges:" << endl;
    for(vector<list<Edge*>>::iterator it = increaseChains.begin(); it != increaseChains.end(); it++) {
        cout << (*it->begin())->source->id;
        for (list<Edge*>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
            cout << " -{" << (*it2)->throughput << "}> " << (*it2)->destination->id;
        }

        cout << endl;
    }
    cout << endl;
}
void runCalculateFlowTest() {
    cout << "Testing Flow calculation algorithm" << endl;

    GraphBuilder builder(6);
    builder.generateTestWeb();
    Graph* g = builder.getResult();

    map<Edge *, int> flow = calculateFlow(g, g->getVertex(0), g->getVertex(5));

    cout << "maxFlow is: " << getMaxFlow(flow, g->getVertex(0)) << endl;

    cout << "Pattern is: \"src -{throughput}> dest : flow\"" << endl;
    for (map<Edge*, int>::iterator i = flow.begin(); i != flow.end() ; i++)
        printf("%lu -{%d}> %lu : %d\n", i->first->source->id, i->first->throughput, i->first->destination->id, i->second);

}

// Add undirected flow calculation :/
int main() {
    runGetPositiveChainsTest();
    runCalculateFlowTest();
}