
// 그래프 간선의 분류
// 양방향 그래프

#include <iostream>
#include <vector>
#include <algorithm>
#include "Print.h"
using namespace std;

// 양방향 인접리스트 그래프
vector<vector<int>> graph =
{
    {1, 2, 7},      // 0
    {0, 3, 5},      // 1
    {0, 4},         // 2
    {1, 4, 5},      // 3
    {2, 3, 6, 7},   // 4
    {3, 1},         // 5
    {4},            // 6
    {0, 4}          // 7
};

vector<int> discovered(graph.size(), -1);
vector<bool> finished(graph.size(), false);
int counter = 0;

// 양방향 간선은 부모를 역방향 간선으로 바로 참조할수도 있는데 이를 방지하기 위해 parent도 저장하여 예외처리한다.
void DFS(int parent, int node)
{
    discovered[node] = counter++;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];

        // 방문한 적 없다면
        if (discovered[next] == -1)
        {
            cout << node << " -> " << next << " : tree edge" << endl;
            DFS(node, next);
        }
        else if (parent != next && discovered[node] != discovered[next])
        {
            cout << node << " -> " << next << " : backward or forward edge" << endl;
        }
    }
}

int main()
{

    DFS(-1, 0);

    return 0;
}