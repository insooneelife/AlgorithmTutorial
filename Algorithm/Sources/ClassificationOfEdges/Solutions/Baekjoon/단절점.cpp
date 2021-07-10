
// 단절점 (CutEdges)
// https://www.acmicpc.net/problem/11266

#pragma warning (disable : 4996)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 인접리스트 그래프
vector<vector<int>> graph;

// 각 정점에 대해 최초 방문 순서를 저장하는 배열
vector<int> indexes;

// 해당 정점이 절단점인지 여부를 저장하는 배열
vector<bool> cutvertex;

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
    int V, E;
    scanf("%d %d", &V, &E);

    graph.assign(V, vector<int>());

    for (int i = 0; i < E; ++i)
    {
        int from, to;
        scanf("%d %d", &from, &to);
        from--;
        to--;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    indexes.assign(graph.size(), -1);
    cutvertex.assign(graph.size(), false);

    // 연결 그래프가 아닐 수 있으므로 모든 정점을 시작점으로 수행한다.
    for (int i = 0; i < V; ++i)
    {
        if(indexes[i] == -1)
            FindCutVertex(i, true);
    }

    vector<int> ans;
    for (int i = 0; i < cutvertex.size(); ++i)
    {
        if (cutvertex[i])
            ans.push_back(i + 1);
    }

    sort(begin(ans), end(ans));

    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i] << " ";
    }

    return 0;
}