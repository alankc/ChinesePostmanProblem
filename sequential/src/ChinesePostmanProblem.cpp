#include <limits>
#include <numeric>
#include <iostream>
#include <chrono>

#include "../include/ChinesePostmanProblem.hpp"

using namespace std;

ChinesePostmanProblem::ChinesePostmanProblem(/* args */)
{
}

ChinesePostmanProblem::~ChinesePostmanProblem()
{
}

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

    auto start = std::chrono::system_clock::now();
    bool tst = mg->isEulerian(oddVertices);
    auto end = std::chrono::system_clock::now();
    cout << oddVertices.size() << "\t";
    //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto elapsed_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << elapsed_1.count() << "\t";

    auto total_elapsed = elapsed_1;

    if (!tst)
    {
        vector<vector<uint64_t>> distances;
        vector<map<uint32_t, list<uint32_t>>> paths;
        start = std::chrono::system_clock::now();
        listPairs(oddVertices, distances, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_2;
        cout << elapsed_2.count() << "\t";

        vector<uint32_t> vec(oddVertices.size());
        std::iota(vec.begin(), vec.end(), 0);
        start = std::chrono::system_clock::now();
        vector<vector<pair<uint32_t, uint32_t>>> pairs = listPairsCombinations(vec);
        end = std::chrono::system_clock::now();
        auto elapsed_3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_3;
        cout << elapsed_3.count() << "\t";

        start = std::chrono::system_clock::now();
        vector<pair<uint32_t, uint32_t>> bestPairs = bestPairsCombination(pairs, distances);
        end = std::chrono::system_clock::now();
        auto elapsed_4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_4;
        cout << elapsed_4.count() << "\t";

        start = std::chrono::system_clock::now();
        modifyGraph(bestPairs, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_5 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_5;
        cout << elapsed_5.count() << "\t";
    }

    uint64_t distance;
    list<uint32_t> path;
    start = std::chrono::system_clock::now();
    mg->hierholzer(startVertex, path, distance);
    end = std::chrono::system_clock::now();
    auto elapsed_6 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    total_elapsed += elapsed_6;
    cout << elapsed_6.count() << "\t";

    cout << total_elapsed.count() << "\t";

    cout << distance << "\t";

    cout << "P:";
    for (auto v : path)
    {
        cout << " " << v;
    }
    cout << endl;
}

vector<pair<uint32_t, uint32_t>> ChinesePostmanProblem::listPairsCombinationsBase(vector<uint32_t> &oddVertices, vector<vector<uint64_t>> &distances)
{
    vector<pair<uint32_t, uint32_t>> final;
    if (oddVertices.size() == 2)
    {
        final.push_back(make_pair(oddVertices[0], oddVertices[1]));
    }
    else
    {
        uint32_t first = *oddVertices.begin();
        oddVertices.erase(oddVertices.begin());

        uint64_t min_distance = numeric_limits<uint64_t>::max();

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
                //verificar se o melhor
                uint64_t total_distance = distancePairCombination(buffer, distances);
                if (total_distance < min_distance)
                {
                    final = buffer;
                    min_distance = total_distance;
                }
            }
        }
    }
    return final;
}

uint64_t ChinesePostmanProblem::distancePairCombination(vector<pair<uint32_t, uint32_t>> &pairCombinations, vector<vector<uint64_t>> &distances)
{
    uint64_t curr_value = 0;
    for (auto &column : pairCombinations)
    {
        curr_value += distances[column.first][column.second];
    }
    return curr_value;
}

void ChinesePostmanProblem::solve_v2(Multigraph *mg, uint32_t startVertex)
{
    this->mg = mg;
    vector<uint32_t> oddVertices;

    auto start = std::chrono::system_clock::now();
    bool tst = mg->isEulerian(oddVertices);
    auto end = std::chrono::system_clock::now();
    cout << oddVertices.size() << "\t";
    //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto elapsed_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout << elapsed_1.count() << "\t";

    auto total_elapsed = elapsed_1;

    if (!tst)
    {
        vector<vector<uint64_t>> distances;
        vector<map<uint32_t, list<uint32_t>>> paths;
        start = std::chrono::system_clock::now();
        listPairs(oddVertices, distances, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_2;
        cout << elapsed_2.count() << "\t";

        vector<uint32_t> vec(oddVertices.size());
        std::iota(vec.begin(), vec.end(), 0);
        start = std::chrono::system_clock::now();
        vector<pair<uint32_t, uint32_t>> bestPairs = listPairsCombinationsBase(vec, distances);
        end = std::chrono::system_clock::now();
        auto elapsed_3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_3;
        cout << elapsed_3.count() << "\t";

        start = std::chrono::system_clock::now();
        modifyGraph(bestPairs, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_4;
        cout << elapsed_4.count() << "\t";
    }

    uint64_t distance;
    list<uint32_t> path;
    start = std::chrono::system_clock::now();
    mg->hierholzer(startVertex, path, distance);
    end = std::chrono::system_clock::now();
    auto elapsed_5 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    total_elapsed += elapsed_5;
    cout << elapsed_5.count() << "\t";

    cout << total_elapsed.count() << "\t";

    cout << distance << "\t";

    cout << "P:";
    for (auto v : path)
    {
        cout << " " << v;
    }
    cout << endl;
}