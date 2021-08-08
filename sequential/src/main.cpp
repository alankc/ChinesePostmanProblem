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

    Edge_t e;
    e.weight = 1.0;

    e.from = 0;
    e.to = 1;
    mg.addEdge(e);
    e.from = 0;
    e.to = 2;
    mg.addEdge(e);
    e.from = 1;
    e.to = 2;
    mg.addEdge(e);

    e.from = 2;
    e.to = 3;
    mg.addEdge(e);
    e.from = 2;
    e.to = 4;
    mg.addEdge(e);
    e.from = 4;
    e.to = 3;
    mg.addEdge(e);

    mg.print();

    vector<uint32_t> ods;
    cout << "É euleriano? " << mg.isEulerian(ods) << endl;
    for (auto v : ods)
        cout << v << "\t " << endl;

    vector<uint32_t> outputPath;
    double distance;
    mg.dijkstra(outputPath, distance);

    return 0;
}