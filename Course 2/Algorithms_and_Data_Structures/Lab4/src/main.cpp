#include "graph/Graph.h"
#include "graph/GraphBuilder.h"
#include "algorithms/algorithms.h"
#include <iostream>

using namespace std;

void runCalculateFlowTest() {
    cout << "Testing Flow calculation algorithm" << endl;

    GraphBuilder builder(5);
    builder.generateFlowTestGraph();
    Graph* g = builder.getResult();

    map<Edge *, int> flow = calculateFlow(g, g->getVertex(0), g->getVertex(5));

    cout << "maxFlow is: " << getMaxFlow(flow, g->getVertex(0)) << endl;

    cout << "Pattern is: \"src -{throughput}> dest : flow\"" << endl;
    for (map<Edge*, int>::iterator i = flow.begin(); i != flow.end() ; i++)
        printf("%lu -{%d}> %lu : %d\n", i->first->source->id, i->first->throughput, i->first->destination->id, i->second);
}
void runCalculateFlowTest2() {
    cout << "Testing Flow calculation algorithm 2" << endl;

    GraphBuilder builder(6);
    builder.generateTestWeb();
    Graph* g = builder.getResult();

    map<Edge *, int> flow = calculateFlow(g, g->getVertex(0), g->getVertex(5));

    cout << "maxFlow is: " << getMaxFlow(flow, g->getVertex(0)) << endl;

    cout << "Pattern is: \"src -{throughput}> dest : flow\"" << endl;
    for (map<Edge*, int>::iterator i = flow.begin(); i != flow.end() ; i++)
        printf("%lu -{%d}> %lu : %d\n", i->first->source->id, i->first->throughput, i->first->destination->id, i->second);
}
void runCalculateFlowOptionGraph() {
    cout << "Running Option Flow calculation algorithm" << endl;

    GraphBuilder builder(6);
    builder.generateOptionWeb();
    Graph* g = builder.getResult();

    map<Edge *, int> flow = calculateFlow(g, g->getVertex(0), g->getVertex(5));

    cout << "maxFlow is: " << getMaxFlow(flow, g->getVertex(0)) << endl;

    cout << "Pattern is: \"src -{throughput}> dest : flow\"" << endl;
    for (map<Edge*, int>::iterator i = flow.begin(); i != flow.end() ; i++)
        printf("%lu -{%d}> %lu : %d\n", i->first->source->id, i->first->throughput, i->first->destination->id, i->second);
}

int main() {
    // runCalculateFlowTest();
    // runCalculateFlowTest2();
    runCalculateFlowOptionGraph();
}