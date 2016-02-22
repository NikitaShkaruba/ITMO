#include "Graph.h"

Graph Graph::generateGraph(size_t vertexCount, size_t edgesCount, int minWeight, int maxWeight) {
    Graph graph(vertexCount, minWeight, maxWeight);

    // Uncomment for true random generation
    // srand(time(0));

    // add root vertex
    Vertex root("root");
    graph.vertexes.push_back(root);

    for (int i = 0; i < vertexCount; ++i) {
        Vertex* neighbour = &vertexes.at(vertexes.size());
        addVertex("a", neighbour);
    }

    for (int i = 0; i < edgesCount - this->edgesCount; i++)
        addEdge(getRandomVertex(), getRandomVertex());

    return graph;
}

Vertex *Graph::getVertex(string content) {
    return nullptr;
}

Vertex* Graph::getRandomVertex() {
    return &vertexes.at(rand() % vertexes.size());
}

Graph::Graph(size_t vertexCount, int minWeight, int maxWeight) {
    // It's really important to preallocate memory coz all the pointers will screw up after every expanding
    vertexes.reserve(vertexCount);

    this->minWeight = minWeight;
    this->maxWeight = maxWeight;
    this->edgesCount = 0;
}

void Graph::addEdge(Vertex* v1, Vertex* v2) {

}

void Graph::addVertex(string name, Vertex* neighbour) {
    Vertex vertex(name);
    vertexes.push_back(vertex);

    Edge* edge = new Edge(&vertex, neighbour, hash(&name.at(0)));
    edgesCount++;
}
void Graph::addVertex(string name, vector<Vertex*> neighbours) {

}

int Graph::hash(char* content) {
    unsigned long magicNumber = 5381;
    int c;

    while (c = *content++)
        magicNumber = ((magicNumber << 5) + magicNumber) + c; /* magicNumber * 33 + c */

    return (int) ((magicNumber % (maxWeight - minWeight + 1)) + minWeight);
}
