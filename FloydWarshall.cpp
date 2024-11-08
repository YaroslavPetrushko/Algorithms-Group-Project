#include "FloydWarshall.h"
#include <algorithm>

std::vector<std::vector<int>> FloydWarshall::computeAllPairsShortestPaths(int n, const std::vector<std::vector<int>>& adjMatrix) {
    std::vector<std::vector<int>> dist = adjMatrix;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT32_MAX && dist[k][j] != INT32_MAX)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    return dist;
}
