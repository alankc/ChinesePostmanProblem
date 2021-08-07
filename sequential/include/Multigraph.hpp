#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP

#include <vector>
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
    vector<vector<double>> adjacencyMatrix;
    vector<uint32_t> neighbors;

public:
    Multigraph(/* args */);
    ~Multigraph();
    void addVertex(Vertex_t &vertex);
    void addEdge(Edge_t &edge);
    void addVertices(vector<Vertex_t> &vertices);
    void addEdges(vector<Edge_t> &edges);
    vector<vector<double>> *getAdjacencyMatrix();
    vector<uint32_t> *getNeighbors;
    bool isEulerian(vector<uint32_t> &oddVertices);
    bool dijkstra(vector<uint32_t> &outputPath, double &distance);
    bool hierholzer(vector<uint32_t> &outputPath, double &distance);
};

#endif