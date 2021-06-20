
// 바이러스 (DFS)
// https://www.acmicpc.net/problem/2606

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

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
    vector<vector<int>> graph(100, vector<int>(100, 0));
    std::vector<bool> v(100, false);

    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        graph[from][to] = 1;
        graph[to][from] = 1;
    }

    int cnt = DFS(graph, v, 0);

    cout << cnt - 1 << endl;
    return 0;
}

