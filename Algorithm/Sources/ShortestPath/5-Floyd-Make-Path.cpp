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
        via.assign(N, vector<long long>(N, -1));

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

    // make path from via table
    void MakePath(int from, int to, vector<int>& path)
    {
        if (via[from][to] == -1)
        {
            path.push_back(from);
            if (from != to)
                path.push_back(to);
        }
        else
        {
            int v = via[from][to];
            MakePath(from, v, path);

            // remove overlap element
            path.pop_back();
            MakePath(v, to, path);
        }
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
                        via[i][j] = k;
                    }
                }
            }
        }       
    }

private:
    int N;
    // all pairs of shortest path
    vector<vector<long long>> apsp;

    // table for reconstruct path
    vector<vector<long long>> via;
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

    vector<int> path;
    floyd.MakePath(0, 4, path);

    Print::Container(path);

    return 0;
}




