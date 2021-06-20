
// DFS와 BFS
// https://www.acmicpc.net/problem/1260


#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// 그래프(인접리스트) 깊이우선탐색
// time complexity     O(V + E)
// input               인접리스트 그래프, 방문기록 배열(N), 탐색시작 노드
// output              방문기록
static void ListGraphDFS(
    const std::vector<std::vector<int>>& graph,
    std::vector<bool>& visited,
    int node)
{
    const int N = graph.size();
    visited[node] = true;
    cout << node + 1 << " ";

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];
        if (!visited[next])
            ListGraphDFS(graph, visited, next);
    }
}

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
        cout << node + 1 << " ";

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
    int n, m, node;
    cin >> n >> m >> node;
    node--;

    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    for (int i = 0; i < n; ++i)
    {
        sort(begin(graph[i]), end(graph[i]));
        auto it = unique(begin(graph[i]), end(graph[i]));
        graph[i].erase(it, end(graph[i]));
    }


    std::vector<bool> v(n, false);
    ListGraphDFS(graph, v, node);
    
    cout << endl;

    ListGraphBFS(graph, node, -1);
    return 0;
}
