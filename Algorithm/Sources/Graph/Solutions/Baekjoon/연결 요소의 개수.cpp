
// 연결 요소의 개수 (그래프, DFS, 연결요소)
// https://www.acmicpc.net/problem/11724

#include <vector>
#include <iostream>
#include <queue>
//#include "Print.h"
using namespace std;


int index = 0;
static void DFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    std::vector<int>& components,
    int node)
{
    const int N = graph.size();
    visited[node] = true;
    components[node] = index;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
        if (!visited[next])
            DFS(graph, visited, components, next);
    }
}

void FindComponents(vector<vector<int>> graph)
{
    const int N = graph.size();
    std::vector<bool> visited(N, false);
    std::vector<int> components(N);
    std::vector<int> t(N, 0);

    for (int i = 0; i < N; ++i)
    {
        if (!visited[i])
        {
            DFS(graph, visited, components, i);
            index++;
        }
    }
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);

    for (int i = 0; i < M; ++i)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    FindComponents(graph);

    cout << index;
    
    return 0;
}
