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
            //defining the elements of the pair of vertices
            //Now the identifier from each odd vertices don't matter anymore.
            //Note that in distances and paths it uses i and j
            //this way is more simple to index the distance matrix 
            pair<uint16_t, uint16_t> p;
            p.first = i;
            p.second = j;

            uint16_t distance;
            list<uint16_t> path;

            //getting the path and distance between the vertices
            //using i and j to get the id of the odd vertices and send to Dijkstra
            mg->dijkstra_boost(oddVertices[i], oddVertices[j], path, distance);
            
            //saving the distance between the vertices
            distances[i][j] = distance;
            distances[j][i] = distance;

            //saving the path between the vertices
            paths[i].insert(make_pair(j, path));
        }
    }
}

vector<vector<pair<uint16_t, uint16_t>>> ChinesePostmanProblem::listPairsCombinations(vector<uint16_t> &oddVertices)
{
    vector<vector<pair<uint16_t, uint16_t>>> final;
    //if there are just two odd vertices, return them as the pairs combinations
    if (oddVertices.size() == 2)
    {
        vector<pair<uint16_t, uint16_t>> buffer;
        buffer.push_back(make_pair(oddVertices[0], oddVertices[1]));
        final.push_back(buffer);
    }
    else
    {
        //erase the first vertex
        uint16_t first = *oddVertices.begin();
        oddVertices.erase(oddVertices.begin());

        //to the rest of vertices, for each one, removed it and call
        //the listPairsCombinations without these two vertices
        for (uint16_t i = 0; i < oddVertices.size(); i++)
        {
            //reset odd_j with oddvertices without first
            auto odd_j = oddVertices;
            uint16_t second = oddVertices[i];
            //erase the vertex i from odd_j
            odd_j.erase(odd_j.begin() + i);

            //call listPairsCombinations passing odd_j. Get the solution to oddVertices without first and second
            auto final_tmp = listPairsCombinations(odd_j);
            //use the solution to create bigger solution ways starting with (first, second)
            for (auto &el : final_tmp)
            {
                vector<pair<uint16_t, uint16_t>> buffer;
                buffer.push_back(make_pair(first, second));
				final.push_back(buffer);
                copy(el.begin(), el.end(), back_inserter(final[final.size()-1]));
            }
        }
    }
    return final;
}

//Deprecated function. It was used in the initial work. But due to memory, it was not used in the final work.
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
    //for each pair in best pairs
    for (auto p : bestPairs)
    {
        //if something wrong, it will result in a Segmentation fault
        auto it = paths[p.first].find(p.second);
        auto it_list = it->second.begin();

        uint16_t curr;
        uint16_t last = *it_list;
        it_list++;

        //duplicate edges in the path between the vertices in p
        while (it_list != it->second.end())
        {
            curr = *it_list;
            mg->addEdge(last, curr);
            last = curr;
            it_list++;
        }
    }
}

//Deprecated function. 
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
    //If there are just two vertices, they are the best solution
    if (oddVertices.size() == 2)
    {
        final.push_back(make_pair(oddVertices[0], oddVertices[1]));
    }
    else
    {
        //works analogously to listPairsCombinations
        //But here, it made just the first call and listPairsCombinations make recursively calls
        uint16_t first = *oddVertices.begin();
        oddVertices.erase(oddVertices.begin());

        uint16_t min_distance = numeric_limits<uint16_t>::max();

        chrono::nanoseconds time_final_tmp(0);
        chrono::nanoseconds time_foor_loop(0);
        chrono::_V2::system_clock::time_point begin;
        chrono::_V2::system_clock::time_point end;
        
        for (uint16_t i = 0; i < oddVertices.size(); i++)
        {
            auto odd_j = oddVertices;
            uint16_t second = oddVertices[i];
            odd_j.erase(odd_j.begin() + i);

            //getting a set o pairs combinations
            //for instance, for oddVertices = {1,2,3,4,5,6}
            //first = 1, and second = 2
            //the result: {(3,4)(5,6)}, {(3,5)(4,6)}, {(3,6)(4,5)}
            begin = std::chrono::system_clock::now();
            auto final_tmp = listPairsCombinations(odd_j);
            end = std::chrono::system_clock::now();
            time_final_tmp += end - begin;

            //defining local minimum
            //Here (1,2) or (first, second) is considered in the solution, then, the result: 
            //{(1,2)(3,4)(5,6)}, {(1,2)(3,5)(4,6)}, {(1,2)(3,6)(4,5)}
            uint32_t min_id = 0;
            uint16_t min_distance_local = numeric_limits<uint16_t>::max();
            begin = std::chrono::system_clock::now();
            for (uint32_t j = 0; j < final_tmp.size(); j++)
            { //searchs the best
                //example, computing distace: 
                //total_distance=distance(1,2) + distance({(3,4)(5,6)})
                //total_distance=distance(1,2) + distance(3,4) + distance(5,6)
                uint16_t total_distance = distances[first][second] + distancePairCombination(final_tmp[j], distances);
                if (total_distance < min_distance_local)
                {
                    min_id = j;
                    min_distance_local = total_distance;
                }
            }
            end = std::chrono::system_clock::now();
            time_foor_loop += end - begin;

            //defining global minimum
            //if this solution is better, it saves it
            if (min_distance_local < min_distance)
            {
                final.clear();
                final.push_back(make_pair(first, second));
                copy(final_tmp[min_id].begin(), final_tmp[min_id].end(), back_inserter(final));

                min_distance = min_distance_local;
            }
        }
        cout << time_final_tmp.count() << "\t" << time_foor_loop.count() << "\t";
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

    //verifying if the graph is eulerian
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
        //listing pairs. Generating variables of distances and paths between pairs.
        vector<vector<uint16_t>> distances;
        vector<map<uint16_t, list<uint16_t>>> paths;
        start = std::chrono::system_clock::now();
        listPairs(oddVertices, distances, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_2;
        cout << elapsed_2.count() << "\t";

        //Getting the best pairs combination. Also known as matching in graphs
        vector<uint16_t> vec(oddVertices.size());
        //generating a vector from 0 to oddVertices.size() - 1;
        //remember, variables "distances" and "paths" have index from 0 to oddVertices.size() - 1 
        std::iota(vec.begin(), vec.end(), 0);
        start = std::chrono::system_clock::now();
        vector<pair<uint16_t, uint16_t>> bestPairs = listPairsCombinationsBase(vec, distances);
        end = std::chrono::system_clock::now();
        auto elapsed_3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_3;
        cout << elapsed_3.count() << "\t";

        //Adding extra edges to make it possible Hierholzer get the eulerian cycle
        start = std::chrono::system_clock::now();
        modifyGraph(bestPairs, paths);
        end = std::chrono::system_clock::now();
        auto elapsed_4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        total_elapsed += elapsed_4;
        cout << elapsed_4.count() << "\t";
    }

    //Running Hierholzer to get the eulerian cycle
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

    //printing the path
    cout << "P:";
    for (auto v : path)
    {
        cout << " " << v;
    }
    cout << endl;
}