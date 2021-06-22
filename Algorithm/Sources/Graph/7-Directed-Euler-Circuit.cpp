
// 오일러 서킷, 오일러 트레일 (방향그래프)

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Print.h"
using namespace std;

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

// 이 그래프가 오일러 트레일을 갖는 그래프인지 판단하기 위해서,
// 차수계산 후, 시작 노드, 끝 노드의 차수를 확인해본다.
// 시작노드 : 노드의 나가는 차수가 들어오는 차수보다 1 크다.
// 끝노드 : 노드의 나가는 차수가 들어오는 차수보다 1 작다.
// 그 외 노드 : 나가는 차수와 들어오는 차수는 같다.

bool CheckEulerTrail(
    const vector<vector<int>>& graph,
    const vector<int>& indegree,
    const vector<int>& outdegree,
    int& start_node,
    int& finish_node)
{
    int startcnt = 0;
    int finishcnt = 0;

    // 시작, 끝 노드는 유일해야함
    for (int i = 0; i < indegree.size(); ++i)
    {
        if (outdegree[i] == indegree[i] + 1)
        {
            start_node = i;
            startcnt++;
        }
        if (outdegree[i] + 1 == indegree[i])
        {
            finish_node = i;
            finishcnt++;
        }
    }
    if (!(startcnt == 1 && finishcnt == 1))
        return false;

    // 그 외에는 같아야함
    for (int i = 0; i < indegree.size(); ++i)
    {
        if (i == start_node || i == finish_node)
            continue;

        if (outdegree[i] != indegree[i])
            return false;
    }

    return true;
}


// euler trail
vector<int> DirectGraphEulerTrail(vector<vector<int>>& graph, int start_node)
{
    vector<int> euler;
    DirectGraphEulerCircuit(graph, euler, start_node);
    reverse(begin(euler), end(euler));
    return euler;
}


void DirectGraphEulerCircuitExample()
{
    const int N = 6;
    vector<vector<int>> multigraph =
    {
        { 0, 0, 1, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 1, 0 },
        { 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 1, 0, 0 }
    };

    vector<int> euler;
    vector<int> indegree;
    vector<int> outdegree;

    MakeDegree(multigraph, indegree, outdegree);
    Print::Container(indegree);
    Print::Container(outdegree);

    if (CheckEulerCircuit(indegree, outdegree))
    {
        euler = DirectGraphEulerCircuit(multigraph, 0);
    }
    Print::Container(euler);
}


// 방향그래프의 오일러 트레일을 찾기 위해서 시작점을 알아야한다.
// 오일러 트레일의 시작점은 나가는 차수가 들어오는 차수보다 하나 많은 노드이다.
void DirectGraphEulerTrailExample()
{
    const int N = 5;
    vector<vector<int>> multigraph =
    {
        { 0, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 1 },
        { 0, 1, 0, 0, 1 },
        { 0, 1, 1, 0, 0 },
        { 0, 0, 0, 1, 0 }
    };

    vector<int> euler;
    vector<int> indegree;
    vector<int> outdegree;
    int start;
    int finish;
    MakeDegree(multigraph, indegree, outdegree);
    Print::Container(indegree);
    Print::Container(outdegree);

    if (CheckEulerTrail(multigraph, indegree, outdegree, start, finish))
    {
        euler = DirectGraphEulerTrail(multigraph, start);
    }

    Print::Container(euler);
}



int main()
{
    DirectGraphEulerCircuitExample();
    DirectGraphEulerTrailExample();
    return 0;
}