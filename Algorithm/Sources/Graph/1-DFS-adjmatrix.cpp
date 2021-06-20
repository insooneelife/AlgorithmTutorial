// Adjacency Matrix Graph DFS

#include <vector>
#include <iostream>
#include <queue>
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

// 그래프(인접행렬) 깊이우선탐색
// time complexity     O(N ^ 2)
// input               인접행렬 그래프(N ^ 2), 방문기록 배열(N), 탐색시작 노드
// { 1, 1, 0 },
// { 1, 1, 0 },
// { 0, 0, 1 }
// output              방문한 노드 수, 방문기록
static void MatrixGraphDFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    int node)
{
    using namespace std;

    const int N = graph.size();
    visited[node] = true;

    cout << node << " ";

    for (int i = 0; i < N; ++i)
    {
        if (graph[node][i] == 1 && !visited[i])
            MatrixGraphDFS(graph, visited, i);
    }
}


int main()
{
    std::vector<bool> v(7, false);
    MatrixGraphDFS(graph, v, 0);
    return 0;
}
