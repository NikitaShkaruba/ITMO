#pragma once

#include <string>
#include <vector>
#include <list>
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

// TODO: consider creation of UndirectedEdge class
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

// Graph is a data structure which points to some vertices, which point to an edges.
// So, two graphs is able to point to same vertices
class Graph {
    friend class GraphBuilder;

public:
    Vertex* getRandomVertex();
    Vertex* getVertex(int id);
    vector<Vertex*> getAllVertices();

    size_t getVerticesAmount();
    size_t getEdgesAmount();

    bool haveCycle(Edge edge);

private:
    Graph(int verticesAmount);

    void DepthFirstSearch(bool marked[], int currentIndex);

    vector<Vertex*> vertices;
    size_t verticesCount;
    size_t edgesCount;
};

