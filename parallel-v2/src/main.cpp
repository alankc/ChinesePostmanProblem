#include <iostream>
#include "../include/ChinesePostmanProblem.hpp"

using namespace std;

//time taskset --cpu-list 0-0 sudo nice -n -19 ./teste g 2 0
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << argv[0] << " n p min_seq" << endl;
        return 0;
    }
    //cout << "Solve V2" << endl;
    //cout << "n_odds isEulerian listPairs time_tmp time_for listPairsCombinationsBase modifyGraph ";
    //cout << "hierholzer total_time total_distance path" << endl;
    //time_tmp and time_for are measuremnents inside listPairsCombinationsBase
    Multigraph mg;
    mg.generateGraph(atoi(argv[1]), atoi(argv[2]));
    ChinesePostmanProblem cpp;
    cpp.solve_v2(&mg, 0, atoi(argv[3]));

    return 0;
}