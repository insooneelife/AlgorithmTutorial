// Adjacency List Graph DFS

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>> graph =
{
    {1, 2},
    {0, 3, 4},
    {0, 5, 6},
    {1},
    {1},
    {2},
    {2}
};

// 그래프(인접리스트) 깊이우선탐색
// time complexity     O(V + E)
// input               인접리스트 그래프, 방문기록 배열(N), 탐색시작 노드
// output              방문기록
static void ListGraphDFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    int node)
{
    const int N = graph.size();
    visited[node] = true;
    cout << node << " ";

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
        if (!visited[next])
            ListGraphDFS(graph, visited, next);
    }
}


int main()
{
    std::vector<bool> v(7, false);
    ListGraphDFS(graph, v, 0);
    return 0;
}
