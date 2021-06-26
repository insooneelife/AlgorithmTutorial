
#include <vector>
#include <iostream>
#include <queue>
#include "Print.h"
using namespace std;

void MakeDegree(
    const vector<vector<int>>& graph,
    vector<int>& indegree,
    vector<int>& outdegree)
{
    const int N = graph.size();

    indegree.clear();
    indegree.assign(N, 0);
    outdegree.clear();
    outdegree.assign(N, 0);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            outdegree[i] += graph[i][j];
            indegree[i] += graph[j][i];
        }
    }
}


int main()
{
    vector<vector<int>> multigraph =
    {
        { 0, 0, 1, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 1, 0, 0 }
    };

    vector<vector<int>> multigraph2 =
    {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 1, 0, 2, 0, 0 },
        { 0, 1, 1, 0, 0, 1, 0 },
        { 0, 0, 0, 1, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 0 },
    };

    vector<int> indegree, outdegree;
    MakeDegree(multigraph2, indegree, outdegree);

    Print::Container(indegree);
    Print::Container(outdegree);

    return 0;
}




