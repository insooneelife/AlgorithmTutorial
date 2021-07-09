
// 그래프 간선의 분류
// 사이클의 존재여부 확인

#include <iostream>
#include <vector>
#include <algorithm>
#include "Print.h"
using namespace std;

// 인접리스트 그래프
vector<vector<int>> graph =
{
    {1, 2, 7},  // 0
    {3},        // 1
    {4},        // 2
    {5},        // 3
    {3, 6, 7},  // 4
    {1},        // 5
    {},         // 6
    {}          // 7
};

vector<int> indexes(graph.size(), -1);
vector<bool> finished(graph.size(), false);
int counter = 0;

// find cycle
void DFS(int node)
{
    indexes[node] = counter++;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];

        // 방문한 적 없다면
        if (indexes[next] == -1)
        {
            DFS(next);
        }
        else if (!finished[next] && indexes[node] > indexes[next])
        {
            cout << "cycle : " << node << " -> " << next << endl;
        }
    }

    finished[node] = true;
}

int main()
{
    DFS(0);

    return 0;
}