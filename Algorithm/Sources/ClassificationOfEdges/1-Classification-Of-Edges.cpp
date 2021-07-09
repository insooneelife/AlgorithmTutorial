
// 그래프 간선의 분류

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

vector<int> discovered(graph.size(), -1);
vector<bool> finished(graph.size(), false);
int counter = 0;

void DFS(int node)
{
    discovered[node] = counter++;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];

        cout << node << " -> " << next;

        // 방문한 적 없다면
        if (discovered[next] == -1)
        {
            cout << " : tree edge" << endl;
            DFS(next);
        }
        else if (discovered[node] < discovered[next])
        {
            cout << " : forward edge" << endl;
        }
        else if (!finished[next])
        {
            cout << " : backward edge" << endl;
        }
        else
        {
            cout << " : cross edge" << endl;
        }
    }

    finished[node] = true;
}

int main()
{

    DFS(0);

    return 0;
}