// 연결 요소들 분류하기

#include <vector>
#include <iostream>
#include <queue>
#include "Print.h"
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

    for (int i = 0; i < N; ++i)
    {
        if (!visited[i])
        {
            DFS(graph, visited, components, i);
            index++;
        }
    }

    Print::Container(components);
}

int main()
{
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

    FindComponents(graph);

    return 0;
}


// 예제 문제 1.
// 연결 요소의 개수
// https://www.acmicpc.net/problem/11724