#pragma once

#include <list>
#include <string>
#include <vector>

using namespace std;
struct Edge; // Is needed for self-include purpose

struct Vertex {
    Vertex(string name) {
        this->name = name;
    }

    string name;
    list<Edge> neighborhood;
};

struct Edge {
    Edge(Vertex* v1, Vertex* v2, int weight) : weight(weight) {
        this->v1 = v1;
        this->v2 = v2;
    }

    Vertex* v1;
    Vertex* v2;
    int weight;
};

class Graph {
public:
    Graph(size_t vertexCount, int minWeight, int maxWeight);

    Graph generateGraph(size_t vertexCount, size_t edgesCount, int minWeight, int maxWeight);
    Vertex* getVertex(string content);

private:
    Vertex *getRandomVertex();
    void addEdge(Vertex *v1, Vertex *v2);
    void addVertex(string name, Vertex *neighbour);
    void addVertex(string name, vector<Vertex *> neighbours);
    int hash(char *content);

    vector<Vertex> vertexes;
    size_t edgesCount;
    int minWeight, maxWeight;
};

