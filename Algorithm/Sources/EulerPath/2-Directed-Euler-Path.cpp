
// 오일러 서킷, 오일러 트레일 (유향그래프)

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Print.h"
using namespace std;

vector<vector<int>> multigraph1 =
{
    { 0, 1, 0, 0, 0 },
    { 0, 0, 1, 1, 0 },
    { 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 1 },
    { 0, 0, 0, 0, 0 }
};

vector<vector<int>> multigraph2 =
{
    { 0, 0, 1, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0 },
    { 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 0, 1, 0, 0 }
};

vector<vector<int>> multigraph3 =
{
    { 0, 0, 1, 0, 0 },
    { 1, 0, 0, 0, 1 },
    { 0, 1, 0, 0, 1 },
    { 0, 1, 1, 0, 0 },
    { 0, 0, 0, 1, 0 }
};

void MakeDegree(
    const vector<vector<int>>& graph,
    vector<int>& indegree,
    vector<int>& outdegree)
{
    const int N = graph.size();

    indegree.clear();
    indegree.assign(N, 0);
    outdegree.clear();
    outdegree.assign(N, 0);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            outdegree[i] += graph[i][j];
            indegree[i] += graph[j][i];
        }
    }
}

// 방향 그래프에서 euler circuit이 성립하려면 모든 노드에 대해 indegree와 outdegree가 같아야한다.
bool CheckEulerCircuit(const vector<int>& indegree, const vector<int>& outdegree)
{
    return indegree == outdegree;
}

// directed graph euler circuit
void DirectGraphEulerCircuit(
    vector<vector<int>>& graph,
    vector<int>& euler,
    int node)
{
    for (int i = 0; i < graph[node].size(); ++i)
    {
        while (graph[node][i] > 0)
        {
            graph[node][i]--;
            DirectGraphEulerCircuit(graph, euler, i);
        }
    }

    euler.push_back(node);
}

// interface
vector<int> DirectGraphEulerCircuit(
    vector<vector<int>>& graph,
    int node)
{
    vector<int> euler;
    DirectGraphEulerCircuit(graph, euler, node);
    reverse(begin(euler), end(euler));

    return euler;
}

// 이 그래프가 오일러 트레일을 갖는 그래프인지 판단하기 위해서 차수계산 후, 시작 정점, 끝 정점의 차수를 확인해본다.
// 시작노드 : 정점의 출력차수가 입력차수보다 1 크다.
// 끝노드 : 정점의 출력차수가 입력차수보다 1 작다.
// 그 외 정점 : 출력차수와 입력차수는 같다.

// 오일러 회로인 경우
// return : true,  start_node : 0,  finish_node : 0

// 오일러 경로인 경우
// return : true,  start_node : 출력차수 - 입력차수가 1인 정점,  finish_node : 입력차수 - 출력차수가 1인 정점

bool CheckEulerTrail(
    const vector<vector<int>>& graph,
    const vector<int>& indegree,
    const vector<int>& outdegree,
    int& start_node,
    int& finish_node)
{
    start_node = 0;
    finish_node = 0;
    int startcnt = 0;
    int finishcnt = 0;

    for (int i = 0; i < indegree.size(); ++i)
    {
        if (outdegree[i] - indegree[i] > 1 || indegree[i] - outdegree[i] > 1)
        {
            return false;
        }
        else if (outdegree[i] - indegree[i] == 1)
        {
            start_node = i;
            startcnt++;
        }
        else if (indegree[i] - outdegree[i] == 1)
        {
            finish_node = i;
            finishcnt++;
        }
    }

    return (startcnt == 0 && finishcnt == 0) || (startcnt == 1 && finishcnt == 1);
}


// euler trail
vector<int> DirectGraphEulerTrail(vector<vector<int>>& graph, int start_node)
{
    vector<int> euler;
    DirectGraphEulerCircuit(graph, euler, start_node);
    reverse(begin(euler), end(euler));
    return euler;
}


void DirectGraphEulerCircuitExample(const vector<vector<int>>& graph)
{
    vector<vector<int>> multigraph = graph;
    vector<int> euler;
    vector<int> indegree;
    vector<int> outdegree;

    MakeDegree(multigraph, indegree, outdegree);
    Print::Container(indegree, "indegree");
    Print::Container(outdegree, "outdegree");

    if (CheckEulerCircuit(indegree, outdegree))
    {
        // 오일러 회로의 경우 아무 정점에서나 시작하여도 무방하다.
        // 이 예제에서는 0번 노드에서 시작한다.
        euler = DirectGraphEulerCircuit(multigraph, 0);
    }
    Print::Container(euler, "euler");
}


// 방향그래프의 오일러 트레일을 찾기 위해서 시작점을 알아야한다.
// 오일러 트레일의 시작점은 나가는 차수가 들어오는 차수보다 하나 많은 노드이다.
void DirectGraphEulerTrailExample(const vector<vector<int>>& graph)
{
    vector<vector<int>> multigraph = graph;
    vector<int> euler;
    vector<int> indegree;
    vector<int> outdegree;
    int start;
    int finish;
    MakeDegree(multigraph, indegree, outdegree);
    Print::Container(indegree, "indegree");
    Print::Container(outdegree, "outdegree");

    if (CheckEulerTrail(multigraph, indegree, outdegree, start, finish))
    {
        euler = DirectGraphEulerTrail(multigraph, start);
    }

    Print::Container(euler, "euler");
}



int main()
{
    cout << "[circuit]" << endl;
    DirectGraphEulerCircuitExample(multigraph3);
    cout << endl;

    cout << "[trail]" << endl;
    DirectGraphEulerTrailExample(multigraph3);
    return 0;
}