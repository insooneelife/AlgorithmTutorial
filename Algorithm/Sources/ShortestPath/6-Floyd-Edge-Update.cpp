
// 플로이드
// 간선 추가 및 최단거리 업데이트

#include <queue>
#include <iostream>
#include <limits>
#include "Print.h"
using namespace std;


// 플로이드 알고리즘
// time complexity     O(V ^ 3)
// input        인접행렬 그래프 (node는 1부터 시작)
// output       모든 정점 쌍에 대한 최단거리
class Floyd
{
public:
    
    // adj element must be set max value if there is no edge
    void MakeFromGraph(int N, const vector<vector<long long>>& graph)
    {
        this->N = N;
        this->apsp = graph;

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (graph[i][j] == 0)
                    apsp[i][j] = numeric_limits<int>::max();

        Make();
    }

    // return max if there is no edge
    long long GetCost(int from, int to) const
    {
        return apsp[from][to];
    }

    // 간선 (from, to)가 그래프에 추가되었을 경우,
    // 플로이드의 모든 쌍 테이블을 갱신한다.
    bool Update(int from, int to, int cost)
    {
        if (apsp[from][to] <= cost)
            return false;

        for (int u = 0; u < N; ++u)
        {
            for (int v = 0; v < N; ++v)
            {
                // 단방향 갱신
                apsp[u][v] = min(apsp[u][v], apsp[u][from] + cost + apsp[to][v]);
            }
        }

        return true;
    }

private:
    void Make()
    {
        for (int i = 0; i < N; ++i)
            apsp[i][i] = 0;

        for (int k = 0; k < N; ++k)
        {
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    if (apsp[i][k] + apsp[k][j] < apsp[i][j])
                    {
                        apsp[i][j] = apsp[i][k] + apsp[k][j];
                    }
                }
            }
        }       
    }

private:
    int N;
    // all pairs of shortest path
    vector<vector<long long>> apsp;
};



int main()
{
    const int V = 5;
    vector<vector<long long>> graph =
    {
        {0, 4, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 2, 0, 5, 0},
        {0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0},
    };
    
    Floyd floyd;
    floyd.MakeFromGraph(V, graph);

    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            cout << floyd.GetCost(u, v) << " ";
        }
        cout << endl;
    }

    floyd.Update(0, 3, 1);

    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            cout << floyd.GetCost(u, v) << " ";
        }
        cout << endl;
    }
    

    return 0;
}




