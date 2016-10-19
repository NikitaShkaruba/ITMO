#include <iostream>
#include <assert.h>
#include "graph/GraphBuilder.h"

using namespace std;

void depthFirstSearchUtil(Graph &g, bool* marked, size_t currentIndex) {
    marked[currentIndex] = true;
    vector<Vertex*> vertices = g.getAllVertices();

    if (vertices[currentIndex] != nullptr)
        for (list<Edge *>::iterator eIt = vertices[currentIndex]->neighborhood.begin(); eIt != vertices[currentIndex]->neighborhood.end(); eIt++)
            if (!marked[(*eIt)->destination->id])
                depthFirstSearchUtil(g, marked, (*eIt)->destination->id);
}

vector<Vertex*> depthFirstSearch(Graph& g, Vertex* source) {
    vector<Vertex*> result;
    bool* marked = new bool[g.getVerticesAmount()];
    for (int i = 0; i < g.getVerticesAmount(); i++)
        marked[i] = 0;

    depthFirstSearchUtil(g, marked, source->id);

    for (int i = 0; i < g.getVerticesAmount(); ++i)
        if (marked[i])
            result.push_back(g.getVertex(i));

    delete[] marked;
    return result;
}
bool contains(vector<Vertex*> vect, Vertex* vertex) {
    for(vector<Vertex*>::iterator it = vect.begin(); it != vect.end(); it++)
        if (*it == vertex)
            return true;

    return false;
}

vector<Vertex*> findVulnerabilitiesInNetwork(Graph &graph) {
    vector<Vertex *> allVertices = graph.getAllVertices();
    map<Vertex *, vector<Vertex *>> connectedComponents;

    // Get all connected vertices
    for (vector<Vertex *>::iterator it = allVertices.begin(); it != allVertices.end(); it++)
        connectedComponents[*it] = depthFirstSearch(graph, *it);

    // Get min ones
    for (vector<Vertex *>::iterator it1 = allVertices.begin(); it1 != allVertices.end(); it1++)
        for (vector<Vertex *>::iterator it2 = allVertices.begin(); it2 != allVertices.end(); it2++)
            if (*it1 != *it2 && connectedComponents.count(*it1) != 0)
                if (contains(connectedComponents[*it1], *it2) && !contains(connectedComponents[*it2], *it1))
                    connectedComponents.erase(*it2);
                else if (contains(connectedComponents[*it1], *it2) && contains(connectedComponents[*it2], *it1))
                    if ((*it1)->terminalsAmount > (*it2)->terminalsAmount)
                        connectedComponents.erase(*it1);
                    else
                        connectedComponents.erase(*it2);

    // Shape result
    vector<Vertex*> result;
    for(map<Vertex*, std::vector<Vertex *>>::iterator it = connectedComponents.begin(); it != connectedComponents.end(); it++)
        result.push_back(it->first);

    return result;
}

void runCustomGraph1Test() {
    cout << "----------Running GraphTest1----------" << endl;

    GraphBuilder graphBuilder(1);
    graphBuilder.generateComputerNetwork1();
    Graph* g = graphBuilder.getResult();

    vector<Vertex*> result = findVulnerabilitiesInNetwork(*g);

    assert(result[0]->id == 0 && result[1]->id == 3);
    assert(result.size() == 2);

    cout << "Expected computers to hack first: 0 3" << endl;
    cout << "Computers to hack first: ";
    for(vector<Vertex*>::iterator it = result.begin(); it != result.end(); it++)
        cout << (*it)->id << " ";
    cout << endl << "Expected computers amount: 2" << endl;
    cout << "Computers amount: " << result.size() << endl << endl;
}
void runCustomGraph2Test() {
    cout << "----------Running GraphTest2----------" << endl;

    GraphBuilder graphBuilder(1);
    graphBuilder.generateComputerNetwork2();
    Graph* g = graphBuilder.getResult();

    vector<Vertex*> result = findVulnerabilitiesInNetwork(*g);

    assert(result[0]->id == 1 && result[1]->id == 7);
    assert(result.size() == 2);

    cout << "Expected computers to hack first: 1 7" << endl;
    cout << "Computers to hack first: ";
    for(vector<Vertex*>::iterator it = result.begin(); it != result.end(); it++)
        cout << (*it)->id << " ";
    cout << endl <<"Expected computers amount: 2" << endl;
    cout << "Computers amount: " << result.size() << endl << endl;
}
int main() {
    runCustomGraph1Test();
    runCustomGraph2Test();

    size_t computersAmount;
    cout << "----------Running custom test----------" << endl;
    cout << "Input Computers count: ";
    cin >> computersAmount;

    GraphBuilder graphBuilder(computersAmount);

    for (int i = 0; i < computersAmount; ++i) {
        cout << "Input amount of connected Terminals to computer[" << i << "] : ";

        int terminalsAmount;
        cin >> terminalsAmount;
        graphBuilder.addVertex(i, terminalsAmount);
    }

    cout << "Input connections:\nFormat: {fromId} {toId}\nInput \"0 0\" to find vulnerabilities" << endl;
    size_t fromId = 0, toId = 0;
    while(true) {
        cin >> fromId;
        cin >> toId;

        if (fromId == 0 && toId == 0)
            break;

        graphBuilder.addEdge(fromId, toId, 0);
    }

    vector<Vertex*> result = findVulnerabilitiesInNetwork(*graphBuilder.getResult());

    cout << "Computers to hack first: ";
    for(vector<Vertex*>::iterator it = result.begin(); it != result.end(); it++)
        cout << (*it)->id << " ";
    cout << endl << "Computers amount: " << result.size() << endl;
}