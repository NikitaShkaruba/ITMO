#pragma once

#include <list>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
struct Edge; // Is needed for self-include purpose

struct Vertex {
    Vertex(int id) : id(id) {}

public:
    const int id;
    list<Edge*> neighborhood;

    Edge* getDuplicateEdge(Edge *pEdge) const;
};

struct Edge {
    Edge(Vertex* v1, Vertex* v2, int weight) : weight(weight) {
        this->source = v1;
        this->destination = v2;
    }

    bool isOpposite(const Edge& other) const {
        return other.destination == this->source && other.source == this->destination && other.weight == this->weight;
    }
    bool equals(const Edge& other) const {
        return other.destination == this->destination && other.source == this->source && other.weight == this->weight;
    }
    bool operator<(const Edge& other) const {
        return this->weight < other.weight;
    }

    Vertex* source;
    Vertex* destination;
    int weight;
};

class Graph {
    friend class GraphBuilder;
public:
    bool haveCycle(Edge edge);
    Vertex* getRandomVertex();
    Vertex* getVertex(int id);
    vector<Vertex*> getAllVertexes();

    size_t getVertexAmount();
    size_t getEdgesAmount();

private:
    Graph(int vertexCount);
    bool DepthFirstSearch(Vertex* start, Vertex* destination);

    vector<Vertex> vertexes;
    size_t edgeCount;
};

