#include <numeric>
#include <iostream>

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

void ChinesePostmanProblem::listPairs(vector<uint32_t> &oddVertices, vector<vector<uint64_t>> &distances, vector<map<uint32_t, list<uint32_t>>> &paths)
{
    distances.resize(oddVertices.size(), vector<uint64_t>(oddVertices.size(), Multigraph::INFINITY));
    paths.resize(oddVertices.size());

    for (uint32_t i = 0; i < oddVertices.size() - 1; i++)
    {
        for (uint32_t j = i + 1; j < oddVertices.size(); j++)
        {
            pair<uint32_t, uint32_t> p;
            p.first = i;
            p.second = j;

            uint64_t distance;
            list<uint32_t> path;

            mg->dijkstra_boost(oddVertices[i], oddVertices[j], path, distance);

            distances[i][j] = distance;
            distances[j][i] = distance;

            paths[i].insert(make_pair(j, path));
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

void ChinesePostmanProblem::modifyGraph(vector<pair<uint32_t, uint32_t>> &bestPairs, vector<map<uint32_t, list<uint32_t>>> &paths)
{
    for (auto p : bestPairs)
    {
        //if something wrong, it will result in a Segmentation fault
        auto it = paths[p.first].find(p.second);
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

void ChinesePostmanProblem::solve(Multigraph *mg, uint32_t startVertex)
{
    this->mg = mg;
    vector<uint32_t> oddVertices;

    if (!mg->isEulerian(oddVertices))
    {
        cout << "Step 1 - Done" << endl;

        vector<vector<uint64_t>> distances;
        vector<map<uint32_t, list<uint32_t>>> paths;
        listPairs(oddVertices, distances, paths);
        cout << "Step 2 - Done" << endl;

        vector<uint32_t> vec(oddVertices.size());
        std::iota(vec.begin(), vec.end(), 0);
        vector<vector<pair<uint32_t, uint32_t>>> pairs = listPairsCombinations(vec);
        cout << "Step 3 - Done" << endl;

        vector<pair<uint32_t, uint32_t>> bestPairs = bestPairsCombination(pairs, distances);
        cout << "Step 4 - Done" << endl;

        modifyGraph(bestPairs, paths);
        cout << "Step 5 - Done" << endl;
    }

    uint64_t distance;
    list<uint32_t> path;
    mg->hierholzer(startVertex, path, distance);
    cout << "Hierholzer - Done" << endl;

    cout << "Total distance: " << distance << endl;
    cout << "Path: ";
    for (auto v : path)
    {
        cout << v << " ";
    }
    cout << endl;
}