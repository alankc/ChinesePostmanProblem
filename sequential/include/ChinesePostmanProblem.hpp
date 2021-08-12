#ifndef CHINESE_POSTMAN_HPP
#define CHINESE_POSTMAN_HPP

#include <map>

#include "Multigraph.hpp"

class ChinesePostmanProblem
{
private:
    Multigraph *mg;
    void listPairs(vector<uint32_t> &oddVertices, vector<vector<uint64_t>> &distances, vector<map<uint32_t, list<uint32_t>>> &paths);
    vector<vector<pair<uint32_t, uint32_t>>> listPairsCombinations(vector<uint32_t> &oddVertices);
    vector<pair<uint32_t, uint32_t>> bestPairsCombination(vector<vector<pair<uint32_t, uint32_t>>> &pairCombinations, vector<vector<uint64_t>> &distances);
    void modifyGraph(vector<pair<uint32_t, uint32_t>> &bestPairs, vector<map<uint32_t, list<uint32_t>>> &paths);

public:
    ChinesePostmanProblem(/* args */);
    ~ChinesePostmanProblem();
    void solve(Multigraph *mg, uint32_t startVertex);
};

#endif