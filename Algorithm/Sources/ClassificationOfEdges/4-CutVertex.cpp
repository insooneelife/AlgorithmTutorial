
// 절단점 (CutVertex, Articulation Point)

#include <iostream>
#include <vector>
#include <algorithm>
#include "Print.h"
using namespace std;

// 인접리스트 그래프
vector<vector<int>> graph =
{
    {1, 2},        // 0
    {0, 2},        // 1
    {0, 1, 3, 5},  // 2
    {2, 4},        // 3
    {3},           // 4
    {2, 6, 8},     // 5
    {5, 7},        // 6
    {6, 8},        // 7
    {5, 7},        // 8
};

// 각 정점에 대해 최초 방문 순서를 저장하는 배열
vector<int> indexes(graph.size(), -1);

// 해당 정점이 절단점인지 여부를 저장하는 배열
vector<bool> cutvertex(graph.size(), false);

// 방문 순서
int counter = 0;

// 절단점을 찾는 알고리즘
// 최초 호출 시 isroot는 true, 그 외의 경우 false
// 모든 서브트리들 중에서 최소의 순서값을 반환한다.
int FindCutVertex(int node, bool isroot)
{
    indexes[node] = counter++;
    int ret = indexes[node];

    // 루트인 경우 자식의 개수에 따라 절단점 여부가 결정되기 때문에, 자식 개수를 카운팅한다.
    int childcnt = 0;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        int next = graph[node][i];

        // 방문된적 없는 경우
        if (indexes[next] == -1)
        {
            childcnt++;
            int subtree = FindCutVertex(next, false);

            // 서브트리의 최소 순서값이 자기자신의 순서값보다 크다는 의미는,
            // 서브트리가 역방향 간선을 갖지 않는다는 의미이므로,
            // 이때 이 정점은 절단점이 된다.
            if (!isroot && subtree >= indexes[node])
            {
                cutvertex[node] = true;
            }
            ret = min(ret, subtree);
        }
        else
        {
            ret = min(ret, indexes[next]);
        }
    }

    if (isroot)
    {
        cutvertex[node] = (childcnt >= 2);
    }

    return ret;
}


int main()
{
    // 현재 0을 루트로 절단점을 찾기 시작했지만,
    // 어떤 값을 루트 노드로 하더라도 같은 결과가 나타난다.
    // 만약 그래프가 여러 컴포넌트로 분리되어 있다면, 모든 정점에 대해 수행해보아야 할 것이다. (indexes[next] == -1 조건 성립 시)
    FindCutVertex(0, true);

    Print::Container(cutvertex);

    return 0;
}