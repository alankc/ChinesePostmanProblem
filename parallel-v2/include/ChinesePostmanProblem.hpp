#ifndef CHINESE_POSTMAN_HPP
#define CHINESE_POSTMAN_HPP

#include <map>

#include "../../common/include/Multigraph.hpp"

class ChinesePostmanProblem
{
private:
    Multigraph *mg;
	uint32_t min_seq;
    void listPairs(vector<uint16_t> &oddVertices, vector<vector<uint16_t>> &distances, vector<map<uint16_t, list<uint16_t>>> &paths);
    vector<vector<pair<uint16_t, uint16_t>>> listPairsCombinations(vector<uint16_t> &oddVertices);
    vector<pair<uint16_t, uint16_t>> bestPairsCombination(vector<vector<pair<uint16_t, uint16_t>>> &pairCombinations, vector<vector<uint16_t>> &distances);
    void modifyGraph(vector<pair<uint16_t, uint16_t>> &bestPairs, vector<map<uint16_t, list<uint16_t>>> &paths);

    vector<pair<uint16_t, uint16_t>> listPairsCombinationsBase(vector<uint16_t> &oddVertices, vector<vector<uint16_t>> &distances);
    uint16_t distancePairCombination(vector<pair<uint16_t, uint16_t>> &pairCombinations, vector<vector<uint16_t>> &distances);
    

public:
    ChinesePostmanProblem(/* args */);
    ~ChinesePostmanProblem();
    void solve(Multigraph *mg, uint16_t startVertex);
    void solve_v2(Multigraph *mg, uint16_t startVertex, uint32_t min_seq);
};

#endif