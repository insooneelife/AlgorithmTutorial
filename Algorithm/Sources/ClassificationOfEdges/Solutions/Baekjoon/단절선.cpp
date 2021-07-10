// 단절선 (Bridges)
// https://www.acmicpc.net/problem/11400

#pragma warning (disable : 4996)

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
//#include "Print.h"
using namespace std;

// 인접리스트 그래프
vector<vector<int>> graph;

// 방문 순서
int counter = 0;

int FindBridges(vector<int>& indexes, vector<pair<int, int>>& bridges, int node, int parent)
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
            int subtree = FindBridges(indexes, bridges, next, node);

            if (subtree > indexes[node])
            {
                bridges.push_back({ min(node, next), max(node, next) });
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
    int V, E;
    scanf("%d %d", &V, &E);

    graph.assign(V, vector<int>());

    for (int i = 0; i < E; ++i)
    {
        int from, to;
        scanf("%d %d", &from, &to);
        from--;
        to--;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    // 각 정점에 대해 최초 방문 순서를 저장하는 배열
    vector<int> indexes(graph.size(), -1);
    vector<pair<int, int>> bridges;

    FindBridges(indexes, bridges, 0, -1);
    sort(begin(bridges), end(bridges));

    printf("%d\n", bridges.size());
    for (int i = 0; i < bridges.size(); ++i)
    {
        printf("%d %d\n", bridges[i].first + 1, bridges[i].second + 1);
    }

    return 0;
}