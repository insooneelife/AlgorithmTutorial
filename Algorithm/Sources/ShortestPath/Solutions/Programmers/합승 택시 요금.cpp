// 합승 택시 요금 (플로이드)
// https://programmers.co.kr/learn/courses/30/lessons/72413

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int V = 201;
long long adj[V][V];

void init_adj()
{
    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            adj[i][j] = std::numeric_limits<int>::max();
        }
    }
}

void set_adj(vector<vector<int>> fares)
{
    for (int i = 0; i < fares.size(); ++i)
    {
        int from = fares[i][0];
        int to = fares[i][1];
        int cost = fares[i][2];

        adj[from][to] = cost;
        adj[to][from] = cost;
    }
}

void floyd()
{
    for (int i = 0; i < V; ++i)
        adj[i][i] = 0;

    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

}



int solution(int n, int s, int a, int b, vector<vector<int>> fares)
{
    init_adj();
    set_adj(fares);
    floyd();

    long long min_cost = numeric_limits<int>::max();
    for (int i = 1; i <= n; ++i)
    {
        long long cost = 0;
        if (i == a)
        {
            cost = adj[s][a] + adj[a][b];
        }
        else if (i == b)
        {
            cost = adj[s][b] + adj[b][a];
        }
        else
        {
            cost = adj[s][i] + adj[i][a] + adj[i][b];
        }

        if (min_cost > cost)
        {
            min_cost = cost;
        }
    }


    int answer = min_cost;
    return answer;
}