
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
    vector<vector<int>> multigraph =
    {
        { 2, 1, 1, 0, 0 },
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


