// 연결 요소들 분류하기

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>> graph =
{
    {4, 8, 13, 14},	// 0 
    {5},           	// 1
    {9, 15}, 	    // 2
    {9}, 	        // 3
    {0, 8}, 	    // 4
    {1, 16, 17},    // 5
    {7, 11},        // 6
    {6, 11},        // 7
    {4, 0, 14},     // 8
    {3, 2, 15},     // 9
    {15},           // 10
    {6, 7},         // 11
    {},             // 12
    {0, 14},        // 13
    {0, 8, 13},     // 14
    {2, 9, 10},     // 15
    {5},            // 16
    {5},            // 17
};

static void DFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    int node)
{
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