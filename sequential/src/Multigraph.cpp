#include "../include/Multigraph.hpp"
#include <limits>
#include <queue>
#include <iostream>
#include <iomanip>

using namespace std;

const uint32_t Multigraph::INFINITY = numeric_limits<uint32_t>::max() / 4;

Multigraph::Multigraph(/* args */)
{
}

Multigraph::Multigraph(uint32_t v)
{
    vertices.resize(v);
    adjacencyMatrix.resize(v);
    for (uint32_t i = 0; i < v; i++)
    {
        adjacencyMatrix[i].resize(v, Multigraph::INFINITY);
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
        adjacencyMatrix[i].push_back(Multigraph::INFINITY);

    //resizing and putting infinity value in the last line
    adjacencyMatrix[last].resize(newSize, Multigraph::INFINITY);
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
        adjacencyMatrix[i].resize(newSize, Multigraph::INFINITY);

    for (uint32_t i = last; i < newSize; i++)
    {
        adjacencyMatrix[i].resize(newSize, Multigraph::INFINITY);
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

vector<vector<uint32_t>> *Multigraph::getAdjacencyMatrix()
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

//first is cost, second is id vertex
typedef pair<uint32_t, uint32_t> pq_pair;
bool Multigraph::dijkstra(uint32_t start, uint32_t end, list<uint32_t> &outputPath, uint64_t &totalDistance)
{
    priority_queue<pq_pair, vector<pq_pair>, greater<pq_pair>> pq;

    vector<uint64_t> distance(vertices.size(), Multigraph::INFINITY);
    vector<int64_t> ancester(vertices.size(), -1);
    vector<bool> visited(vertices.size(), false);

    distance[start] = 0.0;

    pq.push(make_pair(0.0, start));

    while (!pq.empty())
    {
        pq_pair best;
        best = pq.top();
        pq.pop();

        if (best.first == distance[best.second])
        {
            if (best.second == end)
            {
                uint32_t curr = end;
                totalDistance = 0;
                while (curr != start)
                {
                    outputPath.push_front(curr);
                    totalDistance += adjacencyMatrix[curr][ancester[curr]];
                    curr = ancester[curr];
                }
                outputPath.push_front(start);
                return true;
            }

            for (auto n : neighbors[best.second])
            {
                uint64_t tempDist = distance[best.second] + adjacencyMatrix[best.second][n];

                if (tempDist < distance[n])
                {
                    distance[n] = tempDist;
                    ancester[n] = best.second;
                    pq.push(make_pair(tempDist, n));
                }
            }
        }
    }
    return false;
}

bool Multigraph::hierholzer(uint32_t start, list<uint32_t> &outputPath, uint64_t &distance)
{

    return false;
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
            if (e != Multigraph::INFINITY)
                cout << std::setw(10) << e << " ";
                else
                cout << std::setw(10) << "inf" << " ";
        }
        cout << "\n";
    }

    cout << "\n========================================" << endl;
}
