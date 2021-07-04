
// DAG 에서 최단경로, 최장경로

#include <iostream>
#include <vector>
#include <algorithm>
#include "Print.h"
using namespace std;

struct Edge
{
    int vertex;
    int cost;
};

// 인접리스트 그래프
vector<vector<Edge>> graph =
{
    {{1, 3}, {2, 6}},           // A 0
    {{2, 4}, {3, 4}, {4, 11}},  // B 1
    {{3, 8}, {6, 11}},          // C 2
    {{4, -4}, {5, 5}, {6, 2}},  // D 3
    {{7, 9}},                   // E 4
    {{7, 1}},                   // F 5
    {{7, 2}},                   // G 6
    {},                         // H 7
};

vector<bool> visited(graph.size(), false);
vector<int> order;

void DFS(int node)
{
    visited[node] = true;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i].vertex;
        if (!visited[next])
            DFS(next);
    }

    order.push_back(node);
}

void TopologicalSort()
{
    for (int i = 0; i < graph.size(); ++i)
    {
        if (!visited[i])
            DFS(i);
    }

    reverse(begin(order), end(order));
}

// DAG 에서 단일 정점 최단거리 알고리즘
// 위상정렬을 이용하여 O(V + E) 시간에 동작
vector<int> ShortestPathOnDAG(int start)
{
    vector<int> sssp(graph.size(), numeric_limits<int>::max());
    sssp[start] = 0;

    for (int i = 0; i < order.size(); ++i)
    {
        int from = order[i];

        for (int j = 0; j < graph[from].size(); ++j)
        {
            Edge e = graph[from][j];
            int to = e.vertex;
            int cost = e.cost;
            sssp[to] = min(sssp[to], sssp[from] + cost);
        }
    }

    return sssp;
}

vector<int> LongestPathOnDAG(int start)
{
    vector<int> sslp(graph.size(), numeric_limits<int>::max());
    sslp[start] = 0;

    for (int i = 0; i < order.size(); ++i)
    {
        int from = order[i];

        for (int j = 0; j < graph[from].size(); ++j)
        {
            Edge e = graph[from][j];
            int to = e.vertex;
            int cost = -e.cost;
            sslp[to] = min(sslp[to], sslp[from] + cost);
        }
    }

    transform(begin(sslp), end(sslp), begin(sslp), [](int e) { return -e; });

    return sslp;
}

int main()
{
    TopologicalSort();

    vector<int> sssp = ShortestPathOnDAG(0);
    Print::Container(sssp, "[single source shortest distance table]");

    vector<int> sslp = LongestPathOnDAG(0);
    Print::Container(sslp, "[single source longest distance table]");

    return 0;
}