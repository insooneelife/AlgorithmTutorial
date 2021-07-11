// 다리 (CutEdges, Bridges)

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
//#include "Print.h"
using namespace std;

// 인접리스트 그래프
vector<vector<int>> graph =
{
    {1, 2},        // 0
    {0, 2},        // 1
    {0, 1, 3, 5},  // 2
    {2, 4},        // 3
    {3},           // 4
    {2, 6, 8},     // 5
    {5, 7},        // 6
    {6, 8},        // 7
    {5, 7},        // 8
};

// 각 정점에 대해 최초 방문 순서를 저장하는 배열
vector<int> indexes(graph.size(), -1);

vector<pair<int, int>> bridges;

// 방문 순서
int counter = 0;

int FindBridges(int node, int parent)
{
    indexes[node] = ++counter;
    int ret = indexes[node];

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
        if (next == parent)
            continue;

        // 방문된적 없는 경우 (트리 간선)
        if (indexes[next] == -1)
        {
            int subtree = FindBridges(next, node);

            if (subtree > indexes[node])
            {
                bridges.push_back({ node, next });
            }
            ret = min(ret, subtree);
        }
        else
        {
            ret = min(ret, indexes[next]);
        }
    }

    return ret;
}


int main()
{
    FindBridges(0, -1);

    cout << bridges.size() << endl;
    for (int i = 0; i < bridges.size(); ++i)
    {
        cout << bridges[i].first << " " << bridges[i].second << endl;
    }

    return 0;
}