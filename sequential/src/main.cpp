#include <iostream>

#include "../include/Multigraph.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Multigraph mg;
    Vertex_t v;
    v.id = 0;
    mg.addVertex(v);
    v.id = 1;
    mg.addVertex(v);
    v.id = 2;
    mg.addVertex(v);
    v.id = 3;
    mg.addVertex(v);
    v.id = 4;
    mg.addVertex(v);
    v.id = 5;
    mg.addVertex(v);
    v.id = 6;
    mg.addVertex(v);
    v.id = 7;
    mg.addVertex(v);

    Edge_t e;

    e.from = 0;
    e.to = 1;
    e.weight = 10;
    mg.addEdge(e);
    e.from = 0;
    e.to = 2;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 1;
    e.to = 3;
    e.weight = 10;
    mg.addEdge(e);
    e.from = 2;
    e.to = 3;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 3;
    e.to = 4;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 3;
    e.to = 5;
    e.weight = 10;
    mg.addEdge(e);
    e.from = 4;
    e.to = 6;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 5;
    e.to = 6;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 6;
    e.to = 7;
    e.weight = 10;
    mg.addEdge(e);
    e.from = 5;
    e.to = 7;
    e.weight = 1;
    mg.addEdge(e);

    mg.print();

    vector<uint32_t> ods;
    cout << "É euleriano? " << mg.isEulerian(ods) << ": ";
    for (auto v : ods)
        cout << v << " ";

    list<uint32_t> outputPath;
    uint64_t distance;
    mg.dijkstra(0, 7, outputPath, distance);
    cout << "\nPath: ";
    for (auto a : outputPath)
        cout << a << " ";

    cout << "\nDistance: " << distance << endl;

    return 0;
}