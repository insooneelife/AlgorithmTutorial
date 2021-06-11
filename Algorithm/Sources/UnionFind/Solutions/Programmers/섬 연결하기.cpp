
// 섬 연결하기 (Union-Find, 그래프, 크루스칼 MST)
// https://programmers.co.kr/learn/courses/30/lessons/42861

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//#include "Print.h"
using namespace std;

struct RankedUnionFind
{
    vector<int> parent;
    vector<int> rank;

    RankedUnionFind(int n) : parent(n), rank(n, 1)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int Find(int i)
    {
        if (i == parent[i]) return i;
        return parent[i] = Find(parent[i]);
    }

    void Union(int a, int b)
    {
        int root1 = Find(a);
        int root2 = Find(b);

        if (root1 == root2)
            return;

        if (rank[root1] > rank[root2]) swap(root1, root2);
        parent[root1] = root2;

        if (rank[root1] == rank[root2]) ++rank[root2];
    }
};

int Kruskal(int vertices, vector<vector<int>>& edges)
{
    RankedUnionFind uf(vertices);

    sort(begin(edges), end(edges), [](const vector<int>& a, const vector<int>& b) { return a[2] < b[2]; });
    int mst_weight = 0;

    for (int i = 0; i < edges.size(); ++i)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int cost = edges[i][2];

        int ru = uf.Find(u);
        int rv = uf.Find(v);

        if (ru != rv)
        {
            uf.Union(ru, rv);
            mst_weight += cost;
        }
    }
    return mst_weight;
}

int solution(int n, vector<vector<int>> costs)
{
    return Kruskal(n, costs);
}

int main()
{
    int n = 4;
    vector<vector<int>> costs = { {0, 1, 1} ,{0, 2, 2},{1, 2, 5},{1, 3, 1},{2, 3, 8} };

    cout << solution(n, costs);

    return 0;
}
