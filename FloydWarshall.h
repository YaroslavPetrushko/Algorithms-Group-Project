#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include <vector>
#include <utility>
using namespace std;

class FloydWarshall {
public:
    static vector<vector<int>> computeAllPairsShortestPaths(int n, const vector<vector<int>>& adjMatrix);
};

#endif
