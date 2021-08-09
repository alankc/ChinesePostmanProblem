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
    double weight;

} Edge_t;

class Multigraph
{
private:
    vector<Vertex_t> vertices;
    vector<vector<uint32_t>> neighbors;
    vector<vector<double>> adjacencyMatrix;
    const static double INFINITY;
    
public:
    Multigraph(/* args */);
    Multigraph(uint32_t v);
    ~Multigraph();
    void addVertex(Vertex_t &vertex);
    void addEdge(Edge_t &edge);
    void addEdge(uint32_t from, uint32_t to);
    void addVertices(vector<Vertex_t> &newVertices);
    void addEdges(vector<Edge_t> &edges);
    vector<vector<double>> *getAdjacencyMatrix();
    vector<vector<uint32_t>> *getNeighbors();
    bool isEulerian(vector<uint32_t> &oddVertices);
    bool dijkstra(uint32_t start, uint32_t end, list<uint32_t> &outputPath, double &totalDistance);
    bool hierholzer(vector<uint32_t> &outputPath, double &distance);
    void print();
};

#endif