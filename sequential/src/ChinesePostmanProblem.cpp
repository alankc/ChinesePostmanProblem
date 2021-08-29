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

void ChinesePostmanProblem::listPairs(vector<uint16_t> &oddVertices, vector<vector<uint16_t>> &distances, vector<map<uint16_t, list<uint16_t>>> &paths)
{
    distances.resize(oddVertices.size(), vector<uint16_t>(oddVertices.size(), Multigraph::INFINITY));
    paths.resize(oddVertices.size());

    for (uint16_t i = 0; i < oddVertices.size() - 1; i++)
    {
        for (uint16_t j = i + 1; j < oddVertices.size(); j++)
        {
            pair<uint16_t, uint16_t> p;
            p.first = i;
            p.second = j;

            uint16_t distance;
            list<uint16_t> path;

            mg->dijkstra_boost(oddVertices[i], oddVertices[j], path, distance);

            distances[i][j] = distance;
            distances[j][i] = distance;

            paths[i].insert(make_pair(j, path));
        }
    }
}

vector<vector<pair<uint16_t, uint16_t>>> ChinesePostmanProblem::listPairsCombinations(vector<uint16_t> &oddVertices)
{
    vector<vector<pair<uint16_t, uint16_t>>> final;
    if (oddVertices.size() == 2)
    {
        vector<pair<uint16_t, uint16_t>> buffer;
        buffer.push_back(make_pair(oddVertices[0], oddVertices[1]));
        final.push_back(buffer);
    }
    else
    {
        uint16_t first = *oddVertices.begin();
        oddVertices.erase(oddVertices.begin());

        for (uint16_t i = 0; i < oddVertices.size(); i++)
        {
            auto odd_j = oddVertices;
            uint16_t second = oddVertices[i];
            odd_j.erase(odd_j.begin() + i);

            auto final_tmp = listPairsCombinations(odd_j);
            for (auto &el : final_tmp)
            {
                vector<pair<uint16_t, uint16_t>> buffer;
                buffer.push_back(make_pair(first, second));
                copy(el.begin(), el.end(), back_inserter(buffer));
                final.push_back(buffer);
            }
        }
    }
    return final;
}

vector<pair<uint16_t, uint16_t>> ChinesePostmanProblem::bestPairsCombination(vector<vector<pair<uint16_t, uint16_t>>> &pairCombinations, vector<vector<uint16_t>> &distances)
{
    uint16_t min_value = numeric_limits<uint16_t>::max();
    uint16_t min_id = 0;
    for (uint16_t i = 0; i < pairCombinations.size(); i++)
    {
        uint16_t curr_value = 0;
        for (auto &column : pairCombinations[i])
        {
            curr_value += distances[column.first][column.second];
        }
        if (curr_value < min_value)
        {
            min_value = curr_value;
            min_id = i;
        }
    }
    return pairCombinations[min_id];
}

void ChinesePostmanProblem::modifyGraph(vector<pair<uint16_t, uint16_t>> &bestPairs, vector<map<uint16_t, list<uint16_t>>> &paths)
{
    for (auto p : bestPairs)
    {
        //if something wrong, it will result in a Segmentation fault
        auto it = paths[p.first].find(p.second);
        auto it_list = it->second.begin();

        uint16_t curr;
        uint16_t last = *it_list;
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

void ChinesePostmanProblem::solve(Multigraph *mg, uint16_t startVertex)
{
    this->mg = mg;
    vector<uint16_t> oddVertices;

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
        vector<vector<uint16_t>> distances;
        vector<map<uint16_t, list<uint16_t>>> paths;
        start = std::chrono::system_clock::now();
        listPairs(oddVertices, distances, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_2;
        cout << elapsed_2.count() << "\t";

        vector<uint16_t> vec(oddVertices.size());
        std::iota(vec.begin(), vec.end(), 0);
        start = std::chrono::system_clock::now();
        vector<vector<pair<uint16_t, uint16_t>>> pairs = listPairsCombinations(vec);
        end = std::chrono::system_clock::now();
        auto elapsed_3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_3;
        cout << elapsed_3.count() << "\t";

        start = std::chrono::system_clock::now();
        vector<pair<uint16_t, uint16_t>> bestPairs = bestPairsCombination(pairs, distances);
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

    uint16_t distance;
    list<uint16_t> path;
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

vector<pair<uint16_t, uint16_t>> ChinesePostmanProblem::listPairsCombinationsBase(vector<uint16_t> &oddVertices, vector<vector<uint16_t>> &distances)
{
    vector<pair<uint16_t, uint16_t>> final;
    if (oddVertices.size() == 2)
    {
        final.push_back(make_pair(oddVertices[0], oddVertices[1]));
    }
    else
    {
        uint16_t first = *oddVertices.begin();
        oddVertices.erase(oddVertices.begin());

        uint16_t min_distance = numeric_limits<uint16_t>::max();

        for (uint16_t i = 0; i < oddVertices.size(); i++)
        {
            auto odd_j = oddVertices;
            uint16_t second = oddVertices[i];
            odd_j.erase(odd_j.begin() + i);

            auto final_tmp = listPairsCombinations(odd_j);

            //defining local minimum
            uint32_t min_id = 0;
            uint16_t min_distance_local = numeric_limits<uint16_t>::max();
            for (uint32_t j = 0; j < final_tmp.size(); j++)
            { //verificar se o melhor
                uint16_t total_distance = distances[first][second] + distancePairCombination(final_tmp[j], distances);
                if (total_distance < min_distance_local)
                {
                    min_id = j;
                    min_distance_local = total_distance;
                }
            }

            //defining global minimum
            if (min_distance_local < min_distance)
            {
                final.clear();
                final.push_back(make_pair(first, second));
                copy(final_tmp[min_id].begin(), final_tmp[min_id].end(), back_inserter(final));

                min_distance = min_distance_local;
            }
        }
    }
    return final;
}

uint16_t ChinesePostmanProblem::distancePairCombination(vector<pair<uint16_t, uint16_t>> &pairCombinations, vector<vector<uint16_t>> &distances)
{
    uint16_t curr_value = 0;
    for (auto &column : pairCombinations)
    {
        curr_value += distances[column.first][column.second];
    }
    return curr_value;
}

void ChinesePostmanProblem::solve_v2(Multigraph *mg, uint16_t startVertex)
{
    this->mg = mg;
    vector<uint16_t> oddVertices;

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
        vector<vector<uint16_t>> distances;
        vector<map<uint16_t, list<uint16_t>>> paths;
        start = std::chrono::system_clock::now();
        listPairs(oddVertices, distances, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_2;
        cout << elapsed_2.count() << "\t";

        vector<uint16_t> vec(oddVertices.size());
        std::iota(vec.begin(), vec.end(), 0);
        start = std::chrono::system_clock::now();
        vector<pair<uint16_t, uint16_t>> bestPairs = listPairsCombinationsBase(vec, distances);
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

    uint16_t distance;
    list<uint16_t> path;
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