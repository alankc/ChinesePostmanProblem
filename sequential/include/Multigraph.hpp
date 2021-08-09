#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP

#include <vector>
#include <list>
#include <cstdint>

using namespace std;

typedef struct _Vertex_t
{
    uint32_t id;

} Vertex_t;

typedef struct _Edge_t
{
    uint32_t from;
    uint32_t to;
    uint32_t weight;

} Edge_t;

class Multigraph
{
private:
    vector<Vertex_t> vertices;
    vector<vector<uint32_t>> neighbors;
    vector<vector<uint32_t>> adjacencyMatrix;
    const static uint32_t INFINITY;
    
public:
    Multigraph(/* args */);
    Multigraph(uint32_t v);
    ~Multigraph();
    void addVertex(Vertex_t &vertex);
    void addEdge(Edge_t &edge);
    void addEdge(uint32_t from, uint32_t to);
    void addVertices(vector<Vertex_t> &newVertices);
    void addEdges(vector<Edge_t> &edges);
    vector<vector<uint32_t>> *getAdjacencyMatrix();
    vector<vector<uint32_t>> *getNeighbors();
    bool isEulerian(vector<uint32_t> &oddVertices);
    bool dijkstra(uint32_t start, uint32_t end, list<uint32_t> &outputPath, uint64_t &totalDistance);
    bool hierholzer(uint32_t start, list<uint32_t> &outputPath, uint64_t &distance);
    void print();
};

#endif