
// 오일러 서킷, 오일러 트레일 (무향그래프)


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Print.h"
using namespace std;

vector<vector<int>> multigraph1 =
{
    { 0, 1, 1, 0, 0, 0 },
    { 1, 0, 0, 1, 0, 0 },
    { 1, 0, 0, 2, 1, 0 },
    { 0, 1, 2, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1 },
    { 0, 0, 0, 1, 1, 0 }
};

vector<vector<int>> multigraph2 =
{
    { 2, 1, 1, 0, 0 },
    { 1, 0, 1, 1, 1 },
    { 1, 1, 0, 1, 1 },
    { 0, 1, 1, 0, 1 },
    { 0, 1, 1, 1, 0 }
};

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
// 양방향 그래프에서는 양쪽 간선을 제거해준다.
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

// 무향 그래프에서 euler trail은 euler circuit이거나 시작 노드와 끝 노드 외에 모든 노드들은 차수가 짝수개여야 한다.

// 오일러 회로인 경우
// return : true,  start_node : 0,  finish_node : 0

// 오일러 경로인 경우
// return : true,  start_node : 홀수개의 차수를 갖는 정점,  finish_node : 홀수개의 차수를 갖는 정점

bool CheckEulerTrail(const vector<vector<int>>& graph, const vector<int>& degree, vector<int>& start_finish)
{
    for (int i = 0; i < degree.size(); ++i)
    {
        if (degree[i] % 2 != 0)
        {
            start_finish.push_back(i);
        }
    }

    if (start_finish.size() == 0)
    {
        start_finish = { 0, 0 };
        return true;
    }

    return start_finish.size() == 2;
}

// euler trail
// 차수 확인 후 시작점, 끝점만 정확하게 찾았다면,
// 두 점 중 하나로 euler circuit을 수행하면 euler trail이 만들어진다.
vector<int> EulerTrail(vector<vector<int>>& graph, int start_node)
{
    vector<int> euler;
    EulerCircuit(graph, euler, start_node);
    reverse(begin(euler), end(euler));
    return euler;
}

void EulerCircuitExample(const vector<vector<int>>& graph)
{
    vector<vector<int>> multigraph = graph;
    vector<int> degree;
    vector<int> euler;
    MakeDegree(multigraph, degree);
    Print::Container(degree, "degree");

    if (CheckEulerCircuit(degree))
    {
        euler = EulerCircuit(multigraph, 0);
    }

    Print::Container(euler, "euler");
}

void EulerTrailExample(const vector<vector<int>>& graph)
{
    vector<vector<int>> multigraph = graph;
    vector<int> euler;
    vector<int> degree;
    vector<int> start_finish;
    MakeDegree(multigraph, degree);
    Print::Container(degree, "degree");

    if (CheckEulerTrail(multigraph, degree, start_finish))
    {
        euler = EulerTrail(multigraph, start_finish[0]);
    }

    Print::Container(euler, "euler");
}

int main()
{
    cout << "[circuit]" << endl;
    EulerCircuitExample(multigraph1);

    cout << endl;

    cout << "[trail]" << endl;
    EulerTrailExample(multigraph1);

    return 0;
}