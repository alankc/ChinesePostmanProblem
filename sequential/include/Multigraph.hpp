#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP

#include <vector>
#include <list>
#include <cstdint>
#include <unordered_set>

using namespace std;

struct Vertex_t
{
    uint32_t id;

};

struct Edge_t
{
    uint32_t from;
    uint32_t to;
    uint32_t weight;

};

class Multigraph
{
private:
    vector<Vertex_t> vertices;
    vector<unordered_multiset<uint32_t>> neighbors;
    vector<vector<uint32_t>> adjacencyMatrix;
    
public:
    Multigraph(/* args */);
    Multigraph(uint32_t n);
    ~Multigraph();
    void addVertex(Vertex_t &vertex);
    void addEdge(Edge_t &edge);
    void addEdge(uint32_t from, uint32_t to);
    void addEdge(uint32_t from, uint32_t to, uint32_t weight);
    void addVertices(vector<Vertex_t> &newVertices);
    void addEdges(vector<Edge_t> &edges);
    vector<vector<uint32_t>> *getAdjacencyMatrix();
    vector<unordered_multiset<uint32_t>> *getNeighbors();
    bool isEulerian(vector<uint32_t> &oddVertices);
    bool dijkstra(uint32_t start, uint32_t end, list<uint32_t> &outputPath, uint64_t &totalDistance);
    bool dijkstra_boost(uint32_t start, uint32_t end, list<uint32_t> &outputPath, uint64_t &totalDistance);
    bool hierholzer(uint32_t start, list<uint32_t> &outputPath, uint64_t &distance);
    void print();
    void readGraphFromFile(string file);

    /**
     * Generate a graph with 4 + 6n odd vertices
     * @param n number of vertices
    **/
    void generateGraph(uint32_t n);

    const static uint32_t INFINITY;
};

#endif