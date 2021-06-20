// Adjacency List Graph BFS

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>> graph =
{
    {1, 2},
    {0, 3, 4},
    {0, 5, 6},
    {1},
    {1},
    {2},
    {2}
};

// 그래프(인접리스트) 너비우선탐색
// time complexity     O(V + E)
// input               인접리스트 그래프, 탐색시작 노드, 탐색중단 노드
// output              최단방문회수(길이 없는 경우 : -1)
static int ListGraphBFS(const std::vector<std::vector<int>>& graph, int start, int finish)
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

        for (int i = 0; i < graph[node].size(); ++i)
        {
            int next = graph[node][i];
            if (!visited[next])
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
    ListGraphBFS(graph, 0, -1);
    return 0;
}


