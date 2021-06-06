#include <iostream>
#include <vector>
using namespace std;

// 기본 UnionFind (Ranked)
struct UnionFind
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
        if (i == parent[i])
            return i;

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
