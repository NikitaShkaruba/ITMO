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

    Edge* getDuplicateEdge(Edge *pEdge) const;
};

struct Edge {
    Edge(Vertex* v1, Vertex* v2, int weight) : weight(weight) {
        this->source = v1;
        this->destination = v2;
    }

    bool equals(Edge edge) {
        return edge.destination == this->destination && edge.source == this->source && edge.weight == this->weight;
    }

    Vertex* source;
    Vertex* destination;
    int weight;
};

class Graph {
    friend class GraphBuilder;
public:
    Graph(size_t vertexCount);

    bool haveCycle(Edge* edge);
    Vertex* getRandomVertex();
    Vertex* getVertex(string content);
    map<string, Vertex *> getAllVertexes();
    size_t getVertexAmount();
    size_t getEdgesAmount();

private:
    bool DepthFirstSearch(string startVertexName, string destinationName);

    map<string, Vertex> vertexes;
    size_t edgesCount;
};

