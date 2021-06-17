﻿
#include "Header.h"
#include "Data.h"

// 인풋을 통해 인접리스트 그래프를 생성한다.
/*
static std::vector<std::vector<int>> MakeAdjListGraphFromInput(
    int N,
    const std::vector<std::vector<int>>& input,
    bool bigraph = true)
{
    using namespace std;
    vector <vector<int>> graph(N);
    for (const vector<int>& adj : input)
    {
        int from = adj[0] - 1;
        int to = adj[1] - 1;
        int cost = adj[2];

        graph[from].push_back(to);
        if (bigraph)
        {
            graph[to].push_back(from);
        }
    }

    return graph;
}
*/

// 인풋을 통해 인접행렬 그래프를 생성한다.
// input    2D Array Size N, 간선(노드는 1부터 시작), 양방향 여부
// ex)
// [from][to][cost]
// [from][to][cost]
// ...
// [from][to][cost]

// output   인접행렬 그래프
std::vector<std::vector<long long>> MakeAdjArrayGraphFromInput(
    const int N,
    std::vector<std::vector<int>> inputs,
    bool bigraph = true)
{
    using namespace std;
    vector<vector<long long>> graph(N, vector<long long>(N, std::numeric_limits<int>::max()));

    for (int i = 0; i < inputs.size(); ++i)
    {
        int from = inputs[i][0] - 1;
        int to = inputs[i][1] - 1;
        int cost = inputs[i][2];

        graph[from][to] = (long long)cost;
        if (bigraph)
        {
            graph[to][from] = (long long)cost;
        }
    }
    return graph;
}


// 특정 조건에 맞는
// 인접행렬 그래프를 생성한다.
static std::vector<std::vector<int>> MakeAdjArrayGraph(const int N)
{
    using namespace std;

    vector<vector<int>> graph(N, vector<int>(N, 0));

    for (int from = 0; from < N; ++from)
    {
        for (int to = 0; to < N; ++to)
        {
            // 여기에 조건 추가
            bool other_conditions_here = true;
            if (from == to || other_conditions_here)
            {
                graph[from][to] = 1;
                graph[to][from] = 1;
            }
        }
    }
}

// 그래프(인접행렬) 깊이우선탐색
// time complexity     O(N ^ 2)
// input               인접행렬 그래프(N ^ 2), 방문기록 배열(N), 탐색시작 노드
// { 1, 1, 0 },
// { 1, 1, 0 },
// { 0, 0, 1 }
// output              방문한 노드 수, 방문기록
static int ArrayGraphDFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    int node)
{
    using namespace std;

    if (visited[node])
        return 0;

    const int N = graph.size();
    int cnt = 1;
    visited[node] = true;

    for (int i = 0; i < N; ++i)
    {
        if (graph[node][i] == 1 && !visited[i])
            cnt += DFS(graph, visited, i);
    }
    return cnt;
}

// 그래프(인접리스트) 깊이우선탐색
// time complexity     O(V + E)
// input               인접리스트 그래프, 방문기록 배열(N), 탐색시작 노드
// output              방문기록
static void ListGraphDFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    int node)
{
    using namespace std;

    if (visited[node])
        return;

    const int N = graph.size();
    visited[node] = true;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
        if (!visited[next])
            ListGraphDFS(graph, visited, next);
    }
    return;
}




// 그래프(인접행렬) 너비우선탐색
// time complexity     O(N ^ 2)
// input               인접행렬 그래프(N ^ 2), 탐색시작 노드, 탐색중단 노드
// { 1, 1, 0 },
// { 1, 1, 0 },
// { 0, 0, 1 }
// output              최단방문회수(길이 없는 경우 : -1)
static int ArrayGraphBFS(const std::vector<std::vector<int>>& graph, int start, int finish)
{
    using namespace std;
    using Node = pair<int, int>;

    const int N = graph.size();
    vector<bool> visited(N, false);
    queue<Node> que;
    int ret = -1;

    que.push({ start, 1 });
    visited[start] = true;

    while (!que.empty())
    {
        Node state = que.front();
        int node = state.first;
        int cnt = state.second;

        if (node == finish)
        {
            ret = cnt;
            break;
        }

        for (int next = 0; next < N; ++next)
        {
            if (graph[node][next] == 1 && !visited[next])
            {
                que.push({ next, cnt + 1 });
                visited[next] = true;
            }
        }

        que.pop();
    }

    return ret;
}

// 그래프(인접리스트) 너비우선탐색
// time complexity     O(V + E)
// input               인접리스트 그래프, 탐색시작 노드, 탐색중단 노드
// output              최단방문회수(길이 없는 경우 : -1)
static int ListGraphBFS(const std::vector<std::vector<int>>& graph, int start, int finish)
{
    using namespace std;
    using Node = pair<int, int>;

    const int N = graph.size();
    vector<bool> visited(N, false);
    queue<Node> que;
    int ret = -1;

    que.push({ start, 1 });
    visited[start] = true;

    while (!que.empty())
    {
        Node state = que.front();
        int node = state.first;
        int cnt = state.second;

        if (node == finish)
        {
            ret = cnt;
            break;
        }

        for (int i = 0; i < graph[node].size(); ++i)
        {
            int next = graph[node][i];
            if (!visited[next])
            {
                que.push({ next, cnt + 1 });
                visited[next] = true;
            }
        }

        que.pop();
    }

    return ret;
}


// 플로이드 알고리즘
// time complexity     O(V ^ 3)
// input        인접행렬 그래프 (node는 1부터 시작)
// output       모든 정점 쌍에 대한 최단거리
class Floyd
{
public:
    // [from][to][cost]
    // [from][to][cost]
    // ...
    // [from][to][cost]
    void MakeFromInput(int N, const std::vector<std::vector<int>>& inputs)
    {
        this->N = N;
        adj = MakeAdjArrayGraphFromInput(N, inputs);
        Make();
    }

    // adj element must be set max value if there is no edge
    void MakeFromAdj(int N, const std::vector<std::vector<long long>>& adj)
    {
        this->N = N;
        this->adj = adj;
        Make();
    }

    // return max if there is no edge
    long long GetCost(int from, int to) const
    {
        return adj[from][to];
    }

private:
    void Make()
    {
        for (int i = 0; i < N; ++i)
            adj[i][i] = 0;

        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    adj[i][j] = std::min(adj[i][j], adj[i][k] + adj[k][j]);
    }

private:
    int N;
    std::vector<std::vector<long long>> adj;
};