#include "../include/ChinesePostmanProblem.hpp"

ChinesePostmanProblem::ChinesePostmanProblem(/* args */)
{
}

ChinesePostmanProblem::~ChinesePostmanProblem()
{
}

/*void ChinesePostmanProblem::listPairs(vector<uint32_t> &oddVertices, vector<OddPair> &oddPairs)
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
}*/

void ChinesePostmanProblem::listPairs(vector<uint32_t> &oddVertices, vector<vector<uint64_t>> &distances, map<pair<uint32_t, uint32_t>, list<uint32_t>> &paths)
{
    distances.resize(oddVertices.size(), vector<uint64_t>(oddVertices.size(), Multigraph::INFINITY));

    for (uint32_t i = 0; i < oddVertices.size() - 1; i++)
    {
        for (uint32_t j = i + 1; j < oddVertices.size(); j++)
        {
            pair<uint32_t, uint32_t> p;
            p.first = i;
            p.second = j;

            uint64_t distance;
            list<uint32_t> path;

            mg->dijkstra(oddVertices[i], oddVertices[j], path, distance);

            distances[i][j] = distance;
            distances[j][i] = distance;

            paths.insert(make_pair(p, path));
        }
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

vector<pair<uint32_t, uint32_t>> ChinesePostmanProblem::bestPairsCombination(vector<vector<pair<uint32_t, uint32_t>>> &pairCombinations, vector<vector<uint64_t>> &distances)
{
    uint64_t min_value = numeric_limits<uint64_t>::max();
    vector<pair<uint32_t, uint32_t>> min_set;
    for (auto &line : pairCombinations)
    {
        uint64_t curr_value = 0;
        for (auto &column : line)
        {
            curr_value += distances[column.first][column.second];
        }
        if (curr_value < min_value)
        {
            min_value = curr_value;
            min_set = line;
        }
    }
    return min_set;
}

void ChinesePostmanProblem::modifyGraph(vector<pair<uint32_t, uint32_t>> &bestPairs, map<pair<uint32_t, uint32_t>, list<uint32_t>> &paths)
{
    for (auto p : bestPairs)
    {
        auto it = paths.find(p);
        auto it_list = it->second.begin();
        
        uint32_t curr;
        uint32_t last = *it_list;
        it_list++;
        
        while (it_list != it->second.end())
        {
            curr = *it_list;
            mg->addEdge(last, curr);
            last = curr;
            it_list++;
        }
    }
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
        /*map<pair<uint32_t, uint32_t>, PathData> paths;
        listPairs(oddVertices, paths);*/
    }

    uint64_t distance;
    list<uint32_t> path;
    mg->hierholzer(0, path, distance);
}