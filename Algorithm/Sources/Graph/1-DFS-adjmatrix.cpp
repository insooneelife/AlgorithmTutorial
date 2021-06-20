// DFS (Depth First Search)

#include <vector>
#include <iostream>
using namespace std;

// 인접행렬 그래프
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

// 방문 배열
vector<bool> visited(7, false);

// 깊이우선탐색
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