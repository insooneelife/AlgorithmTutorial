
// 가장 먼 노드 (그래프, BFS)
// https://programmers.co.kr/learn/courses/30/lessons/49189

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
//#include "Print.h"
using namespace std;

// 인풋을 통해 인접리스트 그래프를 생성한다.
static std::vector<std::vector<int>> MakeAdjListGraphFromInput(
    int N,
    const std::vector<std::vector<int>>& input,
    bool bigraph = true)
{
    using namespace std;
    vector <vector<int>> graph(N);
    for (const vector<int>& adj : input)
    {
        int from = adj[0] - 1;
        int to = adj[1] - 1;

        graph[from].push_back(to);
        if (bigraph)
        {
            graph[to].push_back(from);
        }
    }

    return graph;
}

// 인접리스트 너비우선탐색
static int BFS(const std::vector<std::vector<int>>& graph, map<int, int>& counts, int start, int finish)
{
    using namespace std;
    using Node = pair<int, int>;

    const int N = graph.size();
    vector<bool> visited(N, false);
    queue<Node> que;
    int ret = -1;

    que.push({ start, 1 });
    visited[start] = true;
    counts[start] = 1;

    while (!que.empty())
    {
        Node state = que.front();
        int node = state.first;
        int cnt = state.second;

        if (node == finish)
        {
            ret = cnt;
            break;
        }
        
        for(int i = 0; i < graph[node].size(); ++i)
        {
            int next = graph[node][i];
            if (!visited[next])
            {
                que.push({ next, cnt + 1 });
                visited[next] = true;
                counts[next] = cnt + 1;
            }
        }

        que.pop();
    }

    return ret;
}

int solution(int n, vector<vector<int>> edge) 
{
    vector<vector<int>> graph = MakeAdjListGraphFromInput(n, edge);
    map<int, int> counts;

    BFS(graph, counts, 0, -1);

    int maxcnt = 0;
    for (auto e : counts)
    {
        maxcnt = max(maxcnt, e.second);
    }

    int answer = 0;
    for (auto e : counts)
    {
        if (e.second == maxcnt)
            answer++;
    }

    return answer;
}

int main()
{
    int n = 6;
    vector<vector<int>> edge = { {3, 6} ,{4, 3},{3, 2},{1, 3},{1, 2},{2, 4},{5, 2} };
    cout << solution(n, edge) << endl;

    return 0;
}