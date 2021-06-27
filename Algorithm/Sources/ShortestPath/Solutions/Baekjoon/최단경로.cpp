
// 최단경로 (Dijkstra)
// https://www.acmicpc.net/problem/1753

#pragma warning (disable : 4996)

#include <queue>
#include <iostream>
#include <limits>
//#include "Print.h"
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

vector<vector<Edge>> graph;

// 다익스트라의 경우 기본 골격은 BFS와 비슷하지만,
// priority queue를 이용한다는 점과,
// 늦게 삽입된 경로가 더 최단일 수도 있기 때문에 그 경우 최단거리를 갱신해주어야 한다는 점이 다르다.
// 또한 갱신을 허용해야하기 때문에 따로 정점 방문 배열을 이용하지 않는데,
// 그로 인해 늦게 삽입된 경로가 기존의 최단경로보다 더 크더라도 덮어씌우는 문제가 발생할 수 있다.
// 그러므로 그 경우에 대한 예외처리가 필요하다.
vector<int> Dijkstra(const vector<vector<Edge>>& graph, int start)
{
    vector<int> distances(graph.size(), numeric_limits<int>::max());

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

        for (int i = 0; i < graph[v].size(); ++i)
        {
            int next = graph[v][i].v;
            int nextdist = dist + graph[v][i].w;

            // 기존의 저장된 next로의 최단거리보다 nextdist가 작은 경우 갱신한다.
            if (nextdist < distances[next])
            {
                distances[next] = nextdist;
                pq.push({ next, nextdist });
            }
        }
    }

    return distances;
}

int main()
{
    int V, E, start;
    scanf("%d %d", &V, &E);
    scanf("%d", &start);
    start--;

    graph.assign(V, vector<Edge>());

    for (int i = 0; i < E; ++i)
    {
        int from, to, weight;
        scanf("%d %d %d", &from, &to, &weight);
        from--;
        to--;
        graph[from].push_back({ to, weight });
    }

    vector<int> dist = Dijkstra(graph, start);

    for (int i = 0; i < dist.size(); ++i)
    {
        if (dist[i] < numeric_limits<int>::max())
        {
            printf("%d\n", dist[i]);
        }
        else
        {
            printf("INF\n", dist[i]);
        }
    }
}