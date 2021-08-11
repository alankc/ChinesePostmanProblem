#ifndef CHINESE_POSTMAN_HPP
#define CHINESE_POSTMAN_HPP

#include "Multigraph.hpp"

typedef struct _OddPair
{
    uint32_t u;
    uint32_t v;
    uint64_t distance;
    list<uint32_t> path;
}OddPair;


class ChinesePostmanProblem
{
private:
    Multigraph *mg;
    void listPairs(vector<uint32_t> &oddVertices, vector<OddPair> &oddPairs);
    vector<vector<pair<uint32_t, uint32_t>>> listPairsCombinations(vector<uint32_t> &oddVertices);
    void bestPairsCombination();
    void modifyGraph();
    void totalDistance();
    void computeEulerianCicle();

public:
    ChinesePostmanProblem(/* args */);
    ~ChinesePostmanProblem();
    void solve();
};

#endif