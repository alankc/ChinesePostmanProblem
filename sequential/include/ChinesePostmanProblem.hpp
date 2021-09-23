#ifndef CHINESE_POSTMAN_HPP
#define CHINESE_POSTMAN_HPP

#include <map>

#include "../../common/include/Multigraph.hpp"

class ChinesePostmanProblem
{
private:
    Multigraph *mg;

    /**
     * Receives a list of odd vertices and generates a list of distances, and a list of paths. Basically a complete graph.
     * For example, with the vertices 1, 2, 3, 4. It generates distances and paths to pairs: (1,2), (1,3), (1,4), (2,3), (2,4), (3,4). 
    **/
    void listPairs(vector<uint16_t> &oddVertices, vector<vector<uint16_t>> &distances, vector<map<uint16_t, list<uint16_t>>> &paths);

    /**
     * Generate pairs combinations.
     * For example, with the vertices 1, 2, 3, 4.  It returns {(1,2)(3,4)}, {(1,3)(2,4)} and {(1,4)(2,3)}
    **/
    vector<vector<pair<uint16_t, uint16_t>>> listPairsCombinations(vector<uint16_t> &oddVertices);

    //Deprecated function. It was used in the initial work. But due to memory, it was not used in the final work.
    vector<pair<uint16_t, uint16_t>> bestPairsCombination(vector<vector<pair<uint16_t, uint16_t>>> &pairCombinations, vector<vector<uint16_t>> &distances);

    /**
     * For each pair of vertices in bestPairs, it duplicates edges that are in the path of these vertices.
    **/
    void modifyGraph(vector<pair<uint16_t, uint16_t>> &bestPairs, vector<map<uint16_t, list<uint16_t>>> &paths);

    /**
     * Calls listPairsCombinations aiming to define the best set of pairs combinations
     * Considering 6 odd vertices {1,2,3,4,5,6} it will make 5 iterations
     * The first element (a,b)- are the vertices first and second removed from oddVertices before call listPairsCombinations
     * listPairsCombinations then return the sets -(x,y)(z,w)
     * 
     * Example:
     *  Iteration 1
     *  (0,1)-(2,3)(4,5)
     *  (0,1)-(2,4)(3,5)
     *  (0,1)-(2,5)(3,4)
     *  localBestSet  = (0,1)(2,4)(3,5)
     *  globalBestset = (0,1)(2,4)(3,5)
     *
     *  Iteration 2 
     *  (0,2)-(1,3)(4,5)
     *  (0,2)-(1,4)(3,5)
     *  (0,2)-(1,5)(3,4)
     *  localBestSet  = (0,2)(1,4)(3,5)
     *  globalBestset = (0,1)(2,4)(3,5)
     *
     *  Iteration 3
     *  (0,3)-(1,2)(4,5)
     *  (0,3)-(1,4)(2,5)
     *  (0,3)-(1,5)(2,4)
     *  localBestSet  = (0,3)(1,5)(2,4)
     *  globalBestset = (0,3)(1,5)(2,4)
     *
     *  Iteration 4 
     *  (0,4)-(1,2)(3,5)
     *  (0,4)-(1,3)(2,5)
     *  (0,4)-(1,5)(2,3)
     *  localBestSet  = (0,4)(1,2)(3,5)
     *  globalBestset = (0,3)(1,5)(2,4)
     *  
     *  Iteration 5 
     *  (0,5)-(1,2)(3,4)
     *  (0,5)-(1,3)(2,4)
     *  (0,5)-(1,4)(2,3)
     *  localBestSet  = (0,5)(1,2)(3,4)
     *  globalBestset = (0,3)(1,5)(2,4)
     * 
     * return globalBestset
    **/
    vector<pair<uint16_t, uint16_t>> listPairsCombinationsBase(vector<uint16_t> &oddVertices, vector<vector<uint16_t>> &distances);

    /**
     * Given a list of pairs combinations, it sum the distance in the path of each pair
     * Example: 
     *  pairCombinations: {(1,2)(3,4)}
     *  distances: (1,2) = 3, (3,4) = 5 
     *  it would return 8
    **/
    uint16_t distancePairCombination(vector<pair<uint16_t, uint16_t>> &pairCombinations, vector<vector<uint16_t>> &distances);

public:
    ChinesePostmanProblem(/* args */);
    ~ChinesePostmanProblem();
    //Deprecated function.
    void solve(Multigraph *mg, uint16_t startVertex);
    /**
     * Solver
     * It prints time spent in each function, the total time, and the eulerian cycle.
    **/
    void solve_v2(Multigraph *mg, uint16_t startVertex);
};

#endif