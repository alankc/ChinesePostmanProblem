#include <iostream>
#include <unordered_set>
#include <iomanip>
#include "../../common/include/Multigraph.hpp"
#include "../include/ChinesePostmanProblem.hpp"

using namespace std;
/*
private static ObjectArrayList<ObjectArrayList<IntArrayList>> getOddVertexCombinations(IntArrayList oddVertices,
                                                                                       ObjectArrayList<IntArrayList> buffer){
    ObjectArrayList<ObjectArrayList<IntArrayList>> toReturn = new ObjectArrayList<>();
    if (oddVertices.isEmpty()) {
        toReturn.add(buffer.clone());
    } else {
        int first = oddVertices.removeInt(0);
        for (int c = 0; c < oddVertices.size(); c++) {
            int second = oddVertices.removeInt(c);
            buffer.add(new IntArrayList(new int[]{first, second}));
            toReturn.addAll(getOddVertexCombinations(oddVertices, buffer));
            buffer.pop();
            oddVertices.add(c, second);
        }
        oddVertices.add(0, first);
    }
    return toReturn;
}
*/

vector<vector<pair<uint32_t, uint32_t>>> teste(vector<uint32_t> odd)
{
    vector<vector<pair<uint32_t, uint32_t>>> final;
    if (odd.size() == 2)
    {
        vector<pair<uint32_t, uint32_t>> buffer;
        buffer.push_back(make_pair(odd[0], odd[1]));
        final.push_back(buffer);
    }
    else
    {
        auto odd_i = odd;
        //auto i_it = min(odd_i.begin(), odd_i.end());
        auto i_it = odd_i.begin();
        uint32_t first = *i_it;
        odd_i.erase(i_it);

        for (uint32_t i = 0; i < odd_i.size(); i++)
        {
            auto odd_j = odd_i;
            uint32_t second = odd_i[i];
            odd_j.erase(odd_j.begin() + i);

            auto final_tmp = teste(odd_j);
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

vector<vector<pair<uint32_t, uint32_t>>> teste2(vector<uint32_t> odd)
{
    vector<vector<pair<uint32_t, uint32_t>>> final;
    if (odd.size() == 2)
    {
        vector<pair<uint32_t, uint32_t>> buffer;
        buffer.push_back(make_pair(odd[0], odd[1]));
        final.push_back(buffer);
    }
    else
    {
        uint32_t first = *odd.begin();
        odd.erase(odd.begin());

        for (uint32_t i = 0; i < odd.size(); i++)
        {
            auto odd_j = odd;
            uint32_t second = odd[i];
            odd_j.erase(odd_j.begin() + i);

            auto final_tmp = teste(odd_j);
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

Multigraph generateGraph0()
{
    Multigraph mg;
    Vertex_t v;
    v.id = 0;
    mg.addVertex(v);
    v.id = 1;
    mg.addVertex(v);
    v.id = 2;
    mg.addVertex(v);
    v.id = 3;
    mg.addVertex(v);
    v.id = 4;
    mg.addVertex(v);
    v.id = 5;
    mg.addVertex(v);
    v.id = 6;
    mg.addVertex(v);
    v.id = 7;
    mg.addVertex(v);
    v.id = 8;
    mg.addVertex(v);

    Edge_t e;

    e.from = 0;
    e.to = 1;
    e.weight = 10;
    mg.addEdge(e);
    //mg.addEdge(e);
    //mg.addEdge(e);
    e.from = 0;
    e.to = 2;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 1;
    e.to = 3;
    e.weight = 10;
    mg.addEdge(e);
    e.from = 2;
    e.to = 3;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 3;
    e.to = 4;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 3;
    e.to = 5;
    e.weight = 10;
    mg.addEdge(e);
    e.from = 4;
    e.to = 6;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 5;
    e.to = 6;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 6;
    e.to = 7;
    e.weight = 10;
    mg.addEdge(e);
    //mg.addEdge(e);
    e.from = 5;
    e.to = 7;
    e.weight = 1;
    mg.addEdge(e);
    //mg.addEdge(e);

    e.from = 0;
    e.to = 8;
    e.weight = 100;
    mg.addEdge(e);
    mg.print();

    e.from = 1;
    e.to = 2;
    e.weight = 100;
    mg.addEdge(e);
    mg.addEdge(3, 5);
    mg.print();
    return mg;
}

Multigraph generateGraph1()
{
    Multigraph mg;
    Vertex_t v;
    v.id = 0;
    mg.addVertex(v);
    v.id = 1;
    mg.addVertex(v);
    v.id = 2;
    mg.addVertex(v);
    v.id = 3;
    mg.addVertex(v);
    v.id = 4;
    mg.addVertex(v);
    v.id = 5;
    mg.addVertex(v);
    v.id = 6;
    mg.addVertex(v);

    Edge_t e;

    e.from = 0;
    e.to = 1;
    e.weight = 10;
    mg.addEdge(e);

    e.from = 0;
    e.to = 2;
    e.weight = 10;
    mg.addEdge(e);

    e.from = 1;
    e.to = 2;
    e.weight = 10;
    mg.addEdge(e);

    e.from = 1;
    e.to = 3;
    e.weight = 100;
    mg.addEdge(e);

    e.from = 2;
    e.to = 3;
    e.weight = 10;
    mg.addEdge(e);

    e.from = 2;
    e.to = 4;
    e.weight = 10;
    mg.addEdge(e);

    e.from = 3;
    e.to = 4;
    e.weight = 1;
    mg.addEdge(e);

    e.from = 3;
    e.to = 5;
    e.weight = 10;
    mg.addEdge(e);

    e.from = 4;
    e.to = 5;
    e.weight = 10;
    mg.addEdge(e);

    e.from = 5;
    e.to = 6;
    e.weight = 1;
    mg.addEdge(e);

    mg.print();

    return mg;
}

Multigraph generateGraph2()
{
    Multigraph mg;
    for (uint32_t i = 0; i < 16; i++)
    {
        Vertex_t v;
        v.id = i;
        mg.addVertex(v);
    }

    for (uint32_t i = 0; i < 4; i++)
    {
        Edge_t e;
        uint32_t j = 4 * i;

        e.from = j;
        e.to = j + 1;
        e.weight = 1;
        mg.addEdge(e);
        e.from = j;
        e.to = j + 2;
        e.weight = 1;
        mg.addEdge(e);
        e.from = j + 1;
        e.to = j + 2;
        e.weight = 1;
        mg.addEdge(e);
        e.from = j + 1;
        e.to = j + 3;
        e.weight = 1;
        mg.addEdge(e);
        e.from = j + 2;
        e.to = j + 3;
        e.weight = 1;
        mg.addEdge(e);
    }

    Edge_t e;
    e.from = 3;
    e.to = 4;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 3;
    e.to = 8;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 3;
    e.to = 12;
    e.weight = 1;
    mg.addEdge(e);

    e.from = 7;
    e.to = 11;
    e.weight = 1;
    mg.addEdge(e);
    e.from = 11;
    e.to = 15;
    e.weight = 1;
    mg.addEdge(e);
    return mg;
}
//time taskset --cpu-list 0-0 sudo nice -n -19 ./teste g 2 0
int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        cout << argv[0] << " solve_algorithm reps n p min_seq" << endl;
        return 0;
    }

    uint32_t reps = atoi(argv[2]);

    if (*argv[1] == '1')
    {
        cout << "Solve V1" << endl;
        cout << "n_odds\tisEulerian\tlistPairs\tlistPairsCombinations\tbestPairsCombination\tmodifyGraph\t";
        cout << "hierholzer\ttotal time\ttotal distance\tpath" << endl;
    }
    else if (*argv[1] == '2')
    {
        cout << "Solve V2" << endl;
        cout << "n_odds\tisEulerian\tlistPairs\tlistPairsCombinationsBase\tmodifyGraph\t";
        cout << "hierholzer\ttotal time\ttotal distance\tpath" << endl;
    }
    for (uint8_t i = 1; i <= reps; i++)
    {
        Multigraph mg;
        mg.generateGraph(atoi(argv[3]), atoi(argv[4]));
        ChinesePostmanProblem cpp;
        if (*argv[1] == '1')
            cpp.solve(&mg, 0);
        else if (*argv[1] == '2')
            cpp.solve_v2(&mg, 0, atoi(argv[5]));
    }

    return 0;
}