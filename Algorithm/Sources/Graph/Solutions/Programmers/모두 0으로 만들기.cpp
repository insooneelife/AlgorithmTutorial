
// 모두 0으로 만들기 (그래프, 트리, DFS)
// https://programmers.co.kr/learn/courses/30/lessons/76503


#include <string>
#include <vector>
#include <iostream>
//#include "Print.h"
using namespace std;

static std::vector<std::vector<int>> MakeAdjListGraphFromInput(
    int N,
    const std::vector<std::vector<int>>& input,
    bool bigraph = true)
{
    using namespace std;
    vector <vector<int>> graph(N);
    for (const vector<int>& adj : input)
    {
        int from = adj[0];
        int to = adj[1];

        graph[from].push_back(to);
        if (bigraph)
        {
            graph[to].push_back(from);
        }
    }

    return graph;
}

long long sums = 0;
static long long ListGraphDFS(
    const std::vector<std::vector<int>>& graph,
    const vector<int>& values,
    std::vector<bool>& visited,
    int node)
{
    using namespace std;

    if (visited[node])
        return 0;

    const int N = graph.size();
    long long sum = values[node];

    visited[node] = true;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
        if (!visited[next])
        {
            sum += ListGraphDFS(graph, values, visited, next);
        }
    }

    sums += abs(sum);
    return sum;
}

long long solution(vector<int> values, vector<vector<int>> edges) 
{
    const int N = values.size();
    std::vector<std::vector<int>> graph = MakeAdjListGraphFromInput(N, edges);
    std::vector<bool> visited(N, false);
    
    long long sum = ListGraphDFS(graph, values, visited, 0);

    if (sum != 0)
        return -1;

    return sums;
}




int main()
{
    vector<int> a = { -5, 0, 2, 1, 2 };
    vector<vector<int>> edges = 
    {
        {0, 1},
        {3, 4},
        {2, 3},
        {0, 3} 
    };

    cout << solution(a, edges);

    return 0;
}