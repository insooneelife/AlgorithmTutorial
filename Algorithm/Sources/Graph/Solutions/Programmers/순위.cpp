
// 순위 (그래프, DFS)
// https://programmers.co.kr/learn/courses/30/lessons/49191

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//#include "Print.h"
using namespace std;

static std::vector<std::vector<int>> MakeAdjArrayGraphFromInput(
    const int N,
    std::vector<std::vector<int>> inputs)
{
    using namespace std;
    vector<vector<int>> graph(N, vector<int>(N, 0));

    for (int i = 0; i < inputs.size(); ++i)
    {
        int from = inputs[i][0] - 1;
        int to = inputs[i][1] - 1;
        graph[from][to] = 1;
    }
    return graph;
}

static int DFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    std::vector<int>& counts,
    int node)
{
    using namespace std;

    if (visited[node])
        return 0;

    int cnt = 1;

    const int N = graph.size();
    visited[node] = true;
    counts[node]++;

    for (int i = 0; i < N; ++i)
    {
        if (graph[node][i] == 1 && !visited[i])
            cnt += DFS(graph, visited, counts, i);
    }
    return cnt;
}

int solution(int n, vector<vector<int>> results) 
{
    std::vector<std::vector<int>> graph = MakeAdjArrayGraphFromInput(n, results);
    vector<int> counts(n, 0);
    
    for (int i = 0; i < n; ++i)
    {
        vector<bool> visited(n, false);
        int cnt = DFS(graph, visited, counts, i) - 1;

        counts[i] += cnt;
        //Print::Container(counts);
    }
        
    return count(begin(counts), end(counts), n);
}

int main()
{
    
    //int n = 5;
    //vector<vector<int>> results = { {4, 3},{4, 2},{3, 2},{1, 2},{2, 5} };

    int n = 9;
    vector<vector<int>> results = {{1, 2}, {1, 3}, {1, 4}, {1, 5}, {6, 1}, {7, 1}, {8, 1}, {9, 1}}; // ans = 1

    auto v = solution(n, results);
    cout << v << endl;


    return 0;
}