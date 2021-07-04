
// 위상정렬

#include <iostream>
#include <vector>
#include <algorithm>
#include "Print.h"
using namespace std;

// 인접리스트 그래프
vector<vector<int>> graph =
{
    {3},        // A 0
    {3},        // B 1
    {0, 1},     // C 2
    {6, 7},     // D 3
    {0, 3, 5},  // E 4
    {10, 9},    // F 5
    {8},        // G 6
    {8, 9},     // H 7
    {11},       // I 8
    {11, 12},   // J 9
    {9},        // K 10
    {},         // L 11
    {}          // M 12
};

vector<bool> visited(graph.size(), false);
vector<int> order;

void DFS(int node)
{
    visited[node] = true;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
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

int main()
{
    
    TopologicalSort();

    for (int i = 0; i < order.size(); ++i)
    {
        cout << (char)(order[i] + 'A') << " ";
    }

    return 0;
}