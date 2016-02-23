#pragma once

#include <list>
#include <string>
#include <vector>
#include <map>

using namespace std;
struct Edge; // Is needed for self-include purpose

struct Vertex {
    Vertex(string name) : name(name) {}
    Vertex() {}

    const string name;
    list<Edge*> neighborhood;
};

struct Edge {
    Edge(Vertex* v1, Vertex* v2, int weight) : weight(weight) {
        this->source = v1;
        this->destination = v2;
    }

    Vertex* source;
    Vertex* destination;
    int weight;
};

class Graph {
    friend class GraphBuilder;
public:
    Graph(size_t vertexCount);

    Vertex* getVertex(string content);
    Vertex *getRandomVertex();
private:

    map<string, Vertex> vertexes;
    size_t edgesCount;
};

