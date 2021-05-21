// DFS (Depth First Search)

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> graph =
{
    { 0, 1, 1, 0, 0, 0, 0 },
    { 1, 0, 0, 1, 1, 0, 0 },
    { 1, 0, 0, 0, 0, 1, 1 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 }
};

vector<bool> visited(7, false);

void DFS(int node)
{
    visited[node] = true;
    cout << node << " ";

    for (int i = 0; i < graph.size(); ++i)
        if (graph[node][i] == 1 && !visited[i])
            DFS(i);
}

int main()
{
    DFS(0);
    return 0;
}