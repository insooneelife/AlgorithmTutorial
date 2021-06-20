
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Print.h"
using namespace std;


// undirected graph euler circuit
void EulerCircuit(
    vector<vector<int>>& graph,
    vector<int>& euler,
    int node)
{
    for (int i = 0; i < graph[node].size(); ++i)
    {
        while (graph[node][i] > 0)
        {
            graph[node][i]--;
            graph[i][node]--;
            EulerCircuit(graph, euler, i);
        }
    }

    euler.push_back(node);
}

// directed graph euler circuit
void DirectGraphEulerCircuit(
    vector<vector<int>>& graph,
    vector<int>& euler,
    int node)
{
    for (int i = 0; i < graph[node].size(); ++i)
    {
        while (graph[node][i] > 0)
        {
            graph[node][i]--;
            DirectGraphEulerCircuit(graph, euler, i);
        }
    }

    euler.push_back(node);
}

// interface
vector<int> EulerCircuit(
    vector<vector<int>>& graph,
    int node, 
    bool directed_graph)
{
    vector<int> euler;
    if (directed_graph)
    {
        DirectGraphEulerCircuit(graph, euler, node);
    }
    else
    {
        EulerCircuit(graph, euler, node);
    }
    reverse(begin(euler), end(euler));

    return euler;
}



int main()
{
    const int N = 6;
    vector<vector<int>> multigraph =
    {
        { 0, 1, 1, 0, 0, 0 },
        { 1, 0, 0, 1, 0, 0 },
        { 1, 0, 0, 2, 1, 0 },
        { 0, 1, 2, 0, 0, 1 },
        { 0, 0, 1, 0, 0, 1 },
        { 0, 0, 0, 1, 1, 0 }
    };

    vector<int> euler = EulerCircuit(multigraph, 0, false);
    Print::Container(euler);

    return 0;
}