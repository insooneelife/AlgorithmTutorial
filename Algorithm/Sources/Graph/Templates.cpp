
#include "Header.h"
#include "Data.h"

// 인풋을 통해 인접리스트 그래프를 생성한다.
struct Edge
{
    int vertex;
    int weight;
};

static std::vector<std::vector<Edge>> MakeAdjListGraphFromInput(
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
        int cost = adj[2];

        graph[from].push_back({to, cost});
        if (bigraph)
        {
            graph[to].push_back({from, cost});
        }
    }

    return graph;
}


// 인풋을 통해 인접행렬 그래프를 생성한다.
// input    2D Array Size N, 간선(노드는 1부터 시작), 양방향 여부
// ex)
// { from1, to1, cost1 }
// { from2, to2, cost2 }
// ...
// { fromE, toE, costE }

// output   인접행렬 그래프
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


// 특정 조건에 맞는
// 인접행렬 그래프를 생성한다.
static std::vector<std::vector<int>> MakeAdjArrayGraph(const int N)
{
    using namespace std;

    vector<vector<int>> graph(N, vector<int>(N, 0));

    for (int from = 0; from < N; ++from)
    {
        for (int to = 0; to < N; ++to)
        {
            // 여기에 조건 추가
            bool other_conditions_here = true;
            if (from == to || other_conditions_here)
            {
                graph[from][to] = 1;
                graph[to][from] = 1;
            }
        }
    }
}


