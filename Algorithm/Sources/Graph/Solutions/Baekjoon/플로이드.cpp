
// 플로이드
// https://www.acmicpc.net/problem/11404

// 시행착오
// 1. 인접행렬 그래프는 초기값을 int의 max값으로 세팅하여야한다.
// 2. GetCost 함수는 long long으로 설계하여야 한다.
// 3. GetCost로 얻은 값이  int의 max이면, 0을 출력한다.

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

// [from][to][cost]
// [from][to][cost]
// ...
// [from][to][cost]
std::vector<std::vector<long long>> MakeAdjArrayGraphFromInput(
    const int N,
    std::vector<std::vector<int>> inputs,
    bool bigraph = true)
{
    using namespace std;
    vector<vector<long long>> graph(N, vector<long long>(N, std::numeric_limits<int>::max()));

    for (int i = 0; i < inputs.size(); ++i)
    {
        int from = inputs[i][0] - 1;
        int to = inputs[i][1] - 1;
        int cost = inputs[i][2];

        graph[from][to] = (long long)cost;
        if (bigraph)
        {
            graph[to][from] = (long long)cost;
        }
    }
    return graph;
}

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


int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    vector<vector<long long>> adj(101, vector<long long>(101, numeric_limits<int>::max()));
    cin >> n;
    cin >> m;

    int a, b, c;
    for (int i = 0; i < m; i++) 
    {
        cin >> a >> b >> c;
        a--;
        b--;
        if (adj[a][b] == 0)
        {
            adj[a][b] = c;
        }
        else
        {
            adj[a][b] = min(adj[a][b], (long long)c);
        }
    }
    

    Floyd floyd;
    floyd.MakeFromAdj(n, adj);

    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            long long cost = floyd.GetCost(i - 1, j - 1);
            cost = (cost == numeric_limits<int>::max()) ? 0 : cost;
            cout << cost << " ";
        }
        cout << endl;
    }
    return 0;
}
