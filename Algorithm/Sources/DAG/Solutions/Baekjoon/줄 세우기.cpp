
// 줄 세우기 (위상정렬)
// https://www.acmicpc.net/problem/2252

#pragma warning (disable : 4996)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void DFS(const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& order, int node)
{
    visited[node] = true;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
        if (!visited[next])
            DFS(graph, visited, order, next);
    }

    order.push_back(node);
}

void TopologicalSort(const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& order)
{
    for (int i = 0; i < graph.size(); ++i)
    {
        if (!visited[i])
            DFS(graph, visited, order, i);
    }

    reverse(begin(order), end(order));
}

int main()
{
    
    int N, M;
    scanf("%d %d", &N, &M);

    vector<vector<int>> graph(N);
    vector<bool> visited(N, false);
    vector<int> order;

    for (int i = 0; i < M; ++i)
    {
        int from, to;
        scanf("%d %d", &from, &to);
        from--;
        to--;
        graph[from].push_back(to);
    }

    TopologicalSort(graph, visited, order);

    for (int i = 0; i < order.size(); ++i)
    {
        printf("%d ", order[i] + 1);
    }

    return 0;
}