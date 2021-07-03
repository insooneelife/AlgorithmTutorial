// 플로이드
// 동적계획법을 이용한 구현

#include <queue>
#include <iostream>
#include <limits>
#include "Print.h"
using namespace std;

const int V = 5;

long long graph[V][V] =
{
    {0, 4, 1, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 2, 0, 5, 0},
    {0, 0, 0, 0, 3},
    {0, 0, 0, 0, 0},
};

long long dp[V][V][V] = { 0 };


void Floyd()
{
    // 간선이 없는 경우 아주 큰 값으로 초기화
    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            if (graph[u][v] == 0)
                graph[u][v] = numeric_limits<int>::max();
        }
    }

    // 모두 아주 큰 값으로 초기화
    for (int k = 0; k < V; ++k)
    {
        for (int u = 0; u < V; ++u)
        {
            for (int v = 0; v < V; ++v)
            {
                dp[k][u][v] = numeric_limits<int>::max();
            }
        }
    }

    // k는 0일 때, 기저값 세팅
    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            if (u != v)
                dp[0][u][v] = min(graph[u][v], graph[u][0] + graph[0][v]);
            else
                dp[0][u][v] = 0;
        }
        cout << endl;
    }


    // 점화식
    for (int k = 1; k < V; ++k)
    {
        for (int u = 0; u < V; ++u)
        {
            for (int v = 0; v < V; ++v)
            {
                dp[k][u][v] = min(dp[k - 1][u][v], dp[k - 1][u][k] + dp[k - 1][k][v]);
            }
        }
    }

}

int main()
{
    Floyd();

    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            cout << dp[4][u][v] << "\t";
        }
        cout << endl;
    }

    return 0;
}

