#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP

#include <vector>
#include <list>
#include <cstdint>
#include <unordered_set>

using namespace std;

/**
 * Struct to represent a vertex 
**/
struct Vertex_t
{
    uint16_t id;
};

/**
 * Struct to represent an edge 
**/
struct Edge_t
{
    uint16_t from;
    uint16_t to;
    uint16_t weight;
};

/**
 * Struct to represent an multigraph 
**/
class Multigraph
{
private:
    //list of vertices
    vector<Vertex_t> vertices;
    //List of vertex neighbors. Adjacency list. List of edges
    //A vertex can have multiple edges with another vertex
    vector<unordered_multiset<uint16_t>> neighbors;
    //Adjacency matrix. Contains the distances
    vector<vector<uint16_t>> adjacencyMatrix;

public:
    Multigraph(/* args */);
    /**
     * Construct a graph with vertices with an index from 0 to n - 1. 
     * It does not creates edges
    **/
    Multigraph(uint16_t n);
    ~Multigraph();
    /**
     * Add a vertex
    **/
    void addVertex(Vertex_t &vertex);
    /**
     * Add an edge
    **/
    void addEdge(Edge_t &edge);
    /**
     * Duplicate and preexisting edge
    **/
    void addEdge(uint16_t from, uint16_t to);
    /**
     * Add edge and set its weight
    **/
    void addEdge(uint16_t from, uint16_t to, uint16_t weight);
    /**
     * add a list of vertices
    **/
    void addVertices(vector<Vertex_t> &newVertices);
    /**
     * add a list of edges
    **/
    void addEdges(vector<Edge_t> &edges);
    /**
     * Return a pointer to the adjancency matrix
    **/
    vector<vector<uint16_t>> *getAdjacencyMatrix();
    /**
     * Return a pointer to the neighbors
    **/
    vector<unordered_multiset<uint16_t>> *getNeighbors();
    /**
     * Verifities if the graph is eulerian
     * @param oddVertices list of odd vertices found
     * @return true if it eulerian
    **/
    bool isEulerian(vector<uint16_t> &oddVertices);
    /**
     * Runs Dijkstra using STL. Not optimized.
     * @param start starting vertex
     * @param end ending vertex
     * @param outputPath the path between start and end
     * @param totalDistance total distance in the path
     * @return true if it found a path
    **/
    bool dijkstra(uint16_t start, uint16_t end, list<uint16_t> &outputPath, uint16_t &totalDistance);
    /**
     * Runs Dijkstra using boost. 
     * Optimized using fibonacci heap.
     * @param start starting vertex
     * @param end ending vertex
     * @param outputPath the path between start and end
     * @param totalDistance total distance in the path
     * @return true if it found a path
    **/
    bool dijkstra_boost(uint16_t start, uint16_t end, list<uint16_t> &outputPath, uint16_t &totalDistance);
    /**
     * Runs hierholzer. 
     * @param start starting vertex
     * @param outputPath the eulerian cycle
     * @param totalDistance total distance in the path
     * @return true if it found a path
    **/
    bool hierholzer(uint16_t start, list<uint16_t> &outputPath, uint16_t &totalDistance);
    /**
     * Print the graph
    **/
    void print();
    /**
     * Read a graph from file
     * @param file path to the file
    **/
    void readGraphFromFile(string file);

    /**
     * Generate a graph with 4 + 6n + 2p odd vertices
    **/
    void generateGraph(uint16_t n, uint16_t p);

    /**
     * Infinity definition
    **/
    const static uint16_t INFINITY;
};

#endif