#include "../include/ChinesePostmanProblem.hpp"

ChinesePostmanProblem::ChinesePostmanProblem(/* args */)
{
}

ChinesePostmanProblem::~ChinesePostmanProblem()
{
}

void ChinesePostmanProblem::listPairs(vector<uint32_t> &oddVertices, vector<OddPair> &oddPairs)
{
    auto it_i = oddVertices.begin();
    while (it_i != oddVertices.end())
    {
        auto it_j = it_i;
        it_j++;
        while (it_j != oddVertices.end())
        {
            OddPair op;
            op.u = *it_i;
            op.v = *it_j;
            mg->dijkstra(op.u, op.v, op.path, op.distance);
            oddPairs.push_back(op);
            it_j++;
        }
        it_i++;
    }
}

vector<vector<pair<uint32_t, uint32_t>>> ChinesePostmanProblem::listPairsCombinations(vector<uint32_t> &oddVertices)
{
    vector<vector<pair<uint32_t, uint32_t>>> final;
    if (oddVertices.size() == 2)
    {
        vector<pair<uint32_t, uint32_t>> buffer;
        buffer.push_back(make_pair(oddVertices[0], oddVertices[1]));
        final.push_back(buffer);
    }
    else
    {
        uint32_t first = *oddVertices.begin();
        oddVertices.erase(oddVertices.begin());

        for (uint32_t i = 0; i < oddVertices.size(); i++)
        {
            auto odd_j = oddVertices;
            uint32_t second = oddVertices[i];
            odd_j.erase(odd_j.begin() + i);

            auto final_tmp = listPairsCombinations(odd_j);
            for (auto &el : final_tmp)
            {
                vector<pair<uint32_t, uint32_t>> buffer;
                buffer.push_back(make_pair(first, second));
                copy(el.begin(), el.end(), back_inserter(buffer));
                final.push_back(buffer);
            }
        }
    }
    return final;
}

void ChinesePostmanProblem::bestPairsCombination()
{
}

void ChinesePostmanProblem::modifyGraph()
{
}

void ChinesePostmanProblem::totalDistance()
{
}

void ChinesePostmanProblem::computeEulerianCicle()
{
}

void ChinesePostmanProblem::solve()
{
    vector<uint32_t> oddVertices;

    if (!mg->isEulerian(oddVertices))
    {
    }

    uint64_t distance;
    list<uint32_t> path;
    mg->hierholzer(0, path, distance);
}