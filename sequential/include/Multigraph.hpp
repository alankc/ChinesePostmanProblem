#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP

#include <vector>
#include <list>
#include <cstdint>
#include <unordered_set>

using namespace std;

struct Vertex_t
{
    uint16_t id;

};

struct Edge_t
{
    uint16_t from;
    uint16_t to;
    uint16_t weight;

};

class Multigraph
{
private:
    vector<Vertex_t> vertices;
    vector<unordered_multiset<uint16_t>> neighbors;
    vector<vector<uint16_t>> adjacencyMatrix;
    
public:
    Multigraph(/* args */);
    Multigraph(uint16_t n);
    ~Multigraph();
    void addVertex(Vertex_t &vertex);
    void addEdge(Edge_t &edge);
    void addEdge(uint16_t from, uint16_t to);
    void addEdge(uint16_t from, uint16_t to, uint16_t weight);
    void addVertices(vector<Vertex_t> &newVertices);
    void addEdges(vector<Edge_t> &edges);
    vector<vector<uint16_t>> *getAdjacencyMatrix();
    vector<unordered_multiset<uint16_t>> *getNeighbors();
    bool isEulerian(vector<uint16_t> &oddVertices);
    bool dijkstra(uint16_t start, uint16_t end, list<uint16_t> &outputPath, uint16_t &totalDistance);
    bool dijkstra_boost(uint16_t start, uint16_t end, list<uint16_t> &outputPath, uint16_t &totalDistance);
    bool hierholzer(uint16_t start, list<uint16_t> &outputPath, uint16_t &totalDistance);
    void print();
    void readGraphFromFile(string file);

    /**
     * Generate a graph with 4 + 6n + 2p odd vertices
     * @param n number of vertices
    **/
    void generateGraph(uint16_t n, uint16_t p);

    const static uint16_t INFINITY;
};

#endif