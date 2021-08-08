#include "../include/Multigraph.hpp"
#include <limits>
#include <queue>
#include <iostream>

using namespace std;

Multigraph::Multigraph(/* args */)
{
}

Multigraph::Multigraph(uint32_t v)
{
    vertices.resize(v);
    adjacencyMatrix.resize(v);
    for (uint32_t i = 0; i < v; i++)
    {
        adjacencyMatrix[i].resize(v, numeric_limits<double>::max());
        adjacencyMatrix[i][i] = 0.0;
    }

    neighbors.resize(v);
}

Multigraph::~Multigraph()
{
}

void Multigraph::addVertex(Vertex_t &vertex)
{
    //add vertex to vertices list
    vertices.push_back(vertex);

    //resize adjacencyMatrix due to new vertex
    uint32_t last = adjacencyMatrix.size();
    uint32_t newSize = adjacencyMatrix.size() + 1;
    adjacencyMatrix.resize(newSize);

    for (uint32_t i = 0; i < last; i++)
        adjacencyMatrix[i].push_back(numeric_limits<double>::max());

    //resizing and putting infinity value in the last line
    adjacencyMatrix[last].resize(newSize, numeric_limits<double>::max());
    adjacencyMatrix[last][last] = 0;

    //resize neighbors matrix due to new vertex
    neighbors.resize(newSize);
}

void Multigraph::addEdge(Edge_t &edge)
{
    adjacencyMatrix[edge.from][edge.to] = edge.weight;
    adjacencyMatrix[edge.to][edge.from] = edge.weight;
    neighbors[edge.from].push_back(edge.to);
    neighbors[edge.to].push_back(edge.from);
}

void Multigraph::addEdge(uint32_t from, uint32_t to)
{
    neighbors[from].push_back(to);
    neighbors[to].push_back(from);
}

void Multigraph::addVertices(vector<Vertex_t> &newVertices)
{
    //add vertex to vertices list
    for (auto &v : newVertices)
        vertices.push_back(v);

    //resize adjacencyMatrix due to new vertex
    uint32_t last = adjacencyMatrix.size();
    uint32_t newSize = adjacencyMatrix.size() + newVertices.size();
    adjacencyMatrix.resize(newSize);

    for (uint32_t i = 0; i < last; i++)
        adjacencyMatrix[i].resize(newSize, numeric_limits<double>::max());

    for (uint32_t i = last; i < newSize; i++)
    {
        adjacencyMatrix[i].resize(newSize, numeric_limits<double>::max());
        adjacencyMatrix[i][i] = 0.0;
    }

    //resize neighbors matrix due to new vertex
    neighbors.resize(newSize);
}

void Multigraph::addEdges(vector<Edge_t> &edges)
{
    for (auto &edge : edges)
    {
        adjacencyMatrix[edge.from][edge.to] = edge.weight;
        adjacencyMatrix[edge.to][edge.from] = edge.weight;
        neighbors[edge.from].push_back(edge.to);
        neighbors[edge.to].push_back(edge.from);
    }
}

vector<vector<double>> *Multigraph::getAdjacencyMatrix()
{
    return &adjacencyMatrix;
}

vector<vector<uint32_t>> *Multigraph::getNeighbors()
{
    return &neighbors;
}

bool Multigraph::isEulerian(vector<uint32_t> &oddVertices)
{
    bool tst = true;
    for (uint32_t i = 0; i < neighbors.size(); i++)
    {
        if ((neighbors[i].size() > 0) && !(neighbors[i].size() % 2 == 0))
        {
            tst = false;
            oddVertices.push_back(i);
        }
    }
    return tst;
}

typedef pair<double, uint32_t> pq_pair;
bool Multigraph::dijkstra(vector<uint32_t> &outputPath, double &distance)
{
    priority_queue<pq_pair, vector<pq_pair>, greater<pq_pair>> pq;

    for (uint32_t i = 10; i > 0; i--)
        pq.push(make_pair(i*3.15, i));

    while(!pq.empty())
    {
        auto a = pq.top();
        pq.pop();
        cout << a.first << " - " << a.second << endl;
    }    
}

bool Multigraph::hierholzer(vector<uint32_t> &outputPath, double &distance)
{
}


void Multigraph::print()
{
    cout << "========================================\n";
    cout << "\nVertices: \n";
    for (auto &v : vertices)
    {
        cout << v.id << "\t";
    }
    cout << "\n";

    cout << "\nNeighbors: \n";
    for (uint32_t i = 0; i < neighbors.size(); i++)
    {
        cout << "[" << i << "]: ";
        for (auto &e : neighbors[i])
        {
            cout << e << " ";
        }
        cout << "\n";
    }

    cout << "\nAdjacency Matrix: \n";
    for (auto &line : adjacencyMatrix)
    {
        for (auto &e : line)
        {
            cout << e << "\t";
        }
        cout << "\n";
    }

    cout << "\n========================================" << endl;
}
