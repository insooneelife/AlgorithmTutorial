
// 다익스트라 (Dijkstra)
// backtrack 테이블을 이용한 경로 생성


#include <queue>
#include <iostream>
#include <limits>
#include "Print.h"
using namespace std;

struct Edge
{
    int v, w;
};

struct Dist
{
    int v, dist;

    bool operator< (const Dist& other) const
    {
        return dist > other.dist;
    }
};


// 다익스트라 알고리즘
// time complexity     O(E * logV)
// input               방향 그래프, 시작 정점
// output              모든 정점으로의 최단거리
vector<int> Dijkstra(const vector<vector<Edge>>& graph, vector<int>& backtrack, int start)
{
    // 각 정점까지의 최단거리를 저장할 배열
    // 초기값은 무한대로 세팅한다.
    vector<int> distances(graph.size(), numeric_limits<int>::max());

    // (정점, 거리) 쌍을 저장하는 우선순위큐
    // 거리가 작은 순으로 꺼낸다.
    priority_queue<Dist> pq;

    distances[start] = 0;
    pq.push({ start, 0 });

    while (!pq.empty())
    {
        int v = pq.top().v;
        int dist = pq.top().dist;
        pq.pop();

        // 기존에 저장된 v로의 최단거리보다 dist가 큰 경우 무시한다.
        if (distances[v] < dist)
            continue;

        // 이 지점에 진입한 노드는 탐색완료된 정점으로 취급된다.

        // 모든 간선에 대해,
        for (int i = 0; i < graph[v].size(); ++i)
        {
            int next = graph[v][i].v;
            int nextdist = dist + graph[v][i].w;

            // 기존의 저장된 next로의 최단거리보다 nextdist가 작은 경우 갱신한다.
            if (nextdist < distances[next])
            {
                distances[next] = nextdist;
                backtrack[next] = v;
                pq.push({ next, nextdist });
            }
        }
    }

    return distances;
}

void PrintPath(const vector<int>& backtrack, int start, int finish)
{
    vector<int> path;
    int node = finish;

    while (backtrack[node] != node)
    {
        path.push_back(node);
        node = backtrack[node];
    }
    path.push_back(node);
    reverse(begin(path), end(path));

    Print::Container(path, "[path]");
}

int main()
{
    vector<vector<Edge>> graph =
    {
        {{1, 4}, {2, 1}},
        {{3, 1}},
        {{1, 2}, {3, 5}},
        {{4, 3}},
        {}
    };
    
    vector<int> backtrack(graph.size());
    int start = 0;
    vector<int> dist = Dijkstra(graph, backtrack, start);

    Print::Container(dist, "[distances]");

    PrintPath(backtrack, start, 4);
}

