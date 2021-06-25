
// 오일러 회로
// https://www.acmicpc.net/problem/1199

// 오일러 서킷, 오일러 트레일 (무향그래프)


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void MakeDegree(
    const vector<vector<int>>& graph,
    vector<int>& degree)
{
    const int N = graph.size();

    degree.clear();
    degree.assign(N, 0);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            degree[i] += graph[i][j];
        }
    }
}

// 무향 그래프에서 euler circuit이 성립하려면 모든 차수는 짝수개여야 한다.
bool CheckEulerCircuit(const vector<int>& degree)
{
    for (int i = 0; i < degree.size(); ++i)
    {
        if (degree[i] % 2 != 0)
        {
            return false;
        }
    }

    return true;
}


// undirected graph euler circuit
void EulerCircuit(
    vector<vector<int>>& graph,
    vector<int>& euler,
    int node)
{
    for (int i = 0; i < graph[node].size(); ++i)
    {
        while (graph[node][i] > 0)
        {
            graph[node][i]--;
            graph[i][node]--;
            EulerCircuit(graph, euler, i);
        }
    }

    euler.push_back(node);
}


// interface
vector<int> EulerCircuit(
    vector<vector<int>>& graph,
    int node)
{
    vector<int> euler;
    EulerCircuit(graph, euler, node);
    reverse(begin(euler), end(euler));
    return euler;
}

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> multigraph(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> multigraph[i][j];

    vector<int> degree;
    vector<int> euler;
    MakeDegree(multigraph, degree);

    if (CheckEulerCircuit(degree))
    {
        euler = EulerCircuit(multigraph, 0);
    }

    for (int i = 0; i < euler.size(); ++i)
    {
        cout << euler[i] + 1 << " ";
    }

    return 0;
}