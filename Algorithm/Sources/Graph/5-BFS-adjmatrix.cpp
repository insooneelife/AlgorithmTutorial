// Adjacency Matrix Graph BFS (Breadth First Search)

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>> graph =
{
    { 0, 1, 1, 0, 0, 0, 0 },
    { 1, 0, 0, 1, 1, 0, 0 },
    { 1, 0, 0, 0, 0, 1, 1 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 }
};

// 그래프(인접행렬) 너비우선탐색
// time complexity     O(N ^ 2)
// input               인접행렬 그래프(N ^ 2), 탐색시작 노드, 탐색중단 노드
// { 1, 1, 0 },
// { 1, 1, 0 },
// { 0, 0, 1 }
// output              최단방문회수(길이 없는 경우 : -1)
static int MatrixGraphBFS(const std::vector<std::vector<int>>& graph, int start, int finish)
{
    using Node = pair<int, int>;

    const int N = graph.size();
    vector<bool> visited(N, false);
    queue<Node> que;
    int ret = -1;

    que.push({ start, 1 });
    visited[start] = true;

    while (!que.empty())
    {
        Node state = que.front();
        int node = state.first;
        int cnt = state.second;

        cout << node << " ";

        if (node == finish)
        {
            ret = cnt;
            break;
        }

        for (int next = 0; next < N; ++next)
        {
            if (graph[node][next] == 1 && !visited[next])
            {
                que.push({ next, cnt + 1 });
                visited[next] = true;
            }
        }

        que.pop();
    }

    return ret;
}

int main()
{
    MatrixGraphBFS(graph, 0, -1);
    return 0;
}
