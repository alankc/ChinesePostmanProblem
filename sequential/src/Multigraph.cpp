#include "../include/Multigraph.hpp"
#include <limits>
#include <queue>
#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>
#include <fstream>
#include <string>
#include <numeric>

using namespace std;

const uint32_t Multigraph::INFINITY = numeric_limits<uint32_t>::max() / 4;

Multigraph::Multigraph(/* args */)
{
}

Multigraph::Multigraph(uint32_t n)
{
    adjacencyMatrix.resize(n);
    for (uint32_t i = 0; i < n; i++)
    {
        Vertex_t v;
        v.id = i;
        vertices.push_back(v);
        adjacencyMatrix[i].resize(n, Multigraph::INFINITY);
        adjacencyMatrix[i][i] = 0.0;
    }

    neighbors.resize(n);
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
    neighbors[edge.from].insert(edge.to);
    neighbors[edge.to].insert(edge.from);
}

void Multigraph::addEdge(uint32_t from, uint32_t to)
{
    neighbors[from].insert(to);
    neighbors[to].insert(from);
}

void Multigraph::addEdge(uint32_t from, uint32_t to, uint32_t weight)
{
    adjacencyMatrix[from][to] = weight;
    adjacencyMatrix[to][from] = weight;
    neighbors[from].insert(to);
    neighbors[to].insert(from);
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
        neighbors[edge.from].insert(edge.to);
        neighbors[edge.to].insert(edge.from);
    }
}

vector<vector<uint32_t>> *Multigraph::getAdjacencyMatrix()
{
    return &adjacencyMatrix;
}

vector<unordered_multiset<uint32_t>> *Multigraph::getNeighbors()
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
typedef pair<uint64_t, uint32_t> pq_pair;
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
        visited[best.second] = true;

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
                if (!visited[n])
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
    }
    return false;
}

#include <boost/heap/fibonacci_heap.hpp>
struct node_heap
{
    uint64_t distance;
    uint32_t vertex;
    node_heap(uint64_t distance, uint32_t vertex) : distance(distance), vertex(vertex) {}
    node_heap() {}
};

struct compare_node
{
    bool operator()(const node_heap &n1, const node_heap &n2) const
    {
        return n1.distance > n2.distance;
    }
};
typedef boost::heap::fibonacci_heap<node_heap, boost::heap::compare<compare_node>> fibonacci_heap_t;
typedef fibonacci_heap_t::handle_type handle_t;
bool Multigraph::dijkstra_boost(uint32_t start, uint32_t end, list<uint32_t> &outputPath, uint64_t &totalDistance)
{
    fibonacci_heap_t fh;
    vector<uint64_t> distance(vertices.size(), Multigraph::INFINITY);
    vector<int64_t> ancester(vertices.size(), -1);
    vector<bool> visited(vertices.size(), false);
    vector<handle_t> nodeHandle;

    for (uint32_t i = 0; i < vertices.size(); i++)
    {
        node_heap nh(Multigraph::INFINITY, vertices[i].id);
        //if (vertices[i].id == start)
        //    nh.distance = 0;
        nodeHandle.push_back(fh.push(nh));
    }

    fh.update(nodeHandle[start], node_heap(0, start));

    distance[start] = 0;

    while (!fh.empty())
    {
        node_heap best = fh.top();
        fh.pop();
        visited[best.vertex] = true;

        if (best.vertex == end)
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

        for (auto n : neighbors[best.vertex])
        {
            if (!visited[n])
            {
                uint64_t tempDist = distance[best.vertex] + adjacencyMatrix[best.vertex][n];
                if (tempDist < distance[n])
                {
                    distance[n] = tempDist;
                    ancester[n] = best.vertex;
                    nodeHandle[n].node_->value.distance = tempDist;
                    fh.update(nodeHandle[n]);
                    //fh.update(nodeHandle[n], node_heap(tempDist, n));
                }
            }
        }
    }
    return false;
}

bool Multigraph::hierholzer(uint32_t start, list<uint32_t> &outputPath, uint64_t &distance)
{
    vector<unordered_multiset<uint32_t>> n(neighbors);

    stack<uint32_t> tempEulerPath;

    tempEulerPath.push(start);
    distance = 0;
    while (!tempEulerPath.empty())
    {
        uint32_t u = tempEulerPath.top();

        if (n[u].size() == 0)
        {
            tempEulerPath.pop();
            outputPath.push_front(u);
        }
        else
        {
            uint32_t v = *n[u].begin();
            distance += adjacencyMatrix[u][v];
            tempEulerPath.push(v);
            n[u].erase(n[u].begin());
            n[v].erase(n[v].find(u));
        }
    }
    return true;
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
                cout << std::setw(10) << "inf"
                     << " ";
        }
        cout << "\n";
    }

    cout << "\n========================================" << endl;
}

void gotoLine(std::ifstream &ifs, uint32_t num)
{
    ifs.seekg(std::ios::beg);
    for (uint32_t i = 0; i < num - 1; i++)
        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Multigraph::readGraphFromFile(string file)
{
    ifstream ifs;
    ifs.open(file, ifstream::in);

    //Read number of vertices
    string line;
    getline(ifs, line);
    stringstream linestream(line);
    getline(linestream, line, ' ');
    getline(linestream, line, ' ');

    uint32_t num_ver = stol(line);
    vertices.resize(num_ver);
    adjacencyMatrix.resize(num_ver);
    for (uint32_t i = 0; i < num_ver; i++)
    {
        adjacencyMatrix[i].resize(num_ver, Multigraph::INFINITY);
        adjacencyMatrix[i][i] = 0.0;
    }

    neighbors.resize(num_ver);

    //Go to line, start of Edges
    gotoLine(ifs, num_ver + 3);

    while (ifs.good())
    {
        string line;
        getline(ifs, line);
        stringstream linestream(line);

        Edge_t e;
        e.weight = 1;

        getline(linestream, line, ' ');
        e.from = stoi(line) - 1;
        getline(linestream, line, ' ');
        e.to = stoi(line) - 1;

        addEdge(e);
    }
}

void Multigraph::generateGraph(uint32_t n)
{
    //4 even vertices + number of odd vertices
    uint64_t nv = 4 + 4 + 6 * n;

    adjacencyMatrix.resize(nv);
    for (uint32_t i = 0; i < nv; i++)
    {
        Vertex_t v;
        v.id = i;
        vertices.push_back(v);
        adjacencyMatrix[i].resize(nv, Multigraph::INFINITY);
        adjacencyMatrix[i][i] = 0.0;
    }

    neighbors.resize(nv);

    //first part
    addEdge(0, 5, 1);
    addEdge(0, 1, 1);
    addEdge(1, 3, 1);
    addEdge(1, 2, 1);
    addEdge(3, 4, 1);
    addEdge(2, 4, 1);
    addEdge(2, 6, 1);
    addEdge(4, 7, 1);
    addEdge(6, 5, 1);
    addEdge(6, 7, 1);

    for (uint64_t i = 8; i < nv; i = i + 6)
    {
        addEdge(i, i - 5, 1);
        addEdge(i + 4, i - 1, 1);
        addEdge(i, i + 1, 1);
        addEdge(i, i + 2, 1);
        addEdge(i + 1, i + 3, 1);
        addEdge(i + 2, i + 3, 1);
        addEdge(i + 2, i + 4, 1);
        addEdge(i + 3, i + 5, 1);
        addEdge(i + 4, i + 5, 1);
    }
}