
// 무향그래프

#include <vector>
#include <iostream>
#include <queue>
#include "Print.h"
using namespace std;

void MakeDegree(
    const vector<vector<int>>& graph,
    vector<int>& degree)
{
    const int N = graph.size();
    degree.clear();
    degree.assign(N, 0);

    // count
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            degree[i] += graph[i][j];
        }
    }
}


int main()
{
    // 다중그래프
    // i, j 까지의 간선의 개수
    vector<vector<int>> multigraph =
    {
        { 0, 1, 1, 0, 0 },
        { 1, 0, 1, 1, 1 },
        { 1, 1, 0, 1, 1 },
        { 0, 1, 1, 0, 1 },
        { 0, 1, 1, 1, 0 }
    };

    vector<int> degree;
    MakeDegree(multigraph, degree);

    Print::Container(degree);

    return 0;
}


