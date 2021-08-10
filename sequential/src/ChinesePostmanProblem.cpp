#include "../include/ChinesePostmanProblem.hpp"

ChinesePostmanProblem::ChinesePostmanProblem(/* args */)
{
}

ChinesePostmanProblem::~ChinesePostmanProblem()
{
}

void ChinesePostmanProblem::listPairs(list<uint32_t> &oddVertices, vector<OddPair> &oddPairs)
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

void ChinesePostmanProblem::listPairsCombinations()
{
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