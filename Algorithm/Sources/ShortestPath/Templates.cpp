
#include "Header.h"
#include "Data.h"

// 플로이드 알고리즘
// time complexity     O(V ^ 3)
// input        인접행렬 그래프 (node는 1부터 시작)
// output       모든 정점 쌍에 대한 최단거리
class Floyd
{
public:
    // [from][to][cost]
    // [from][to][cost]
    // ...
    // [from][to][cost]
    void MakeFromInput(int N, const std::vector<std::vector<int>>& inputs)
    {
        this->N = N;
        adj = MakeAdjArrayGraphFromInput(N, inputs);
        Make();
    }

    // adj element must be set max value if there is no edge
    void MakeFromAdj(int N, const std::vector<std::vector<long long>>& adj)
    {
        this->N = N;
        this->adj = adj;
        Make();
    }

    // return max if there is no edge
    long long GetCost(int from, int to) const
    {
        return adj[from][to];
    }

private:
    void Make()
    {
        for (int i = 0; i < N; ++i)
            adj[i][i] = 0;

        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    adj[i][j] = std::min(adj[i][j], adj[i][k] + adj[k][j]);
    }

private:
    int N;
    std::vector<std::vector<long long>> adj;
};