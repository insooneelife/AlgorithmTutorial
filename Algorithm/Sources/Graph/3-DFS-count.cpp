// 연결된 노드 개수 카운팅

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>> graph =
{
    { 0, 1, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 1, 1 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 }
};

static int DFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    int node)
{
    if (visited[node])
        return 0;

    const int N = graph.size();
    visited[node] = true;

    int cnt = 1;
    for (int i = 0; i < N; ++i)
    {
        if (graph[node][i] == 1 && !visited[i])
            cnt += DFS(graph, visited, i);
    }
    return cnt;
}


int main()
{
    std::vector<bool> v(7, false);
    int cnt = DFS(graph, v, 0);

    cout << cnt << endl;
    return 0;
}


// 연습 문제 1.
// 바이러스
// https://www.acmicpc.net/problem/2606