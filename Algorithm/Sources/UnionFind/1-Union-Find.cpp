// 상호 배타적 집합
// 단순한 구현
// 각 원소의 부모 원소가 저장될 parent 배열을 정의한다.

// Init 
// 시작 시, 모든 원소는 각각이 유일한 집합으로 표현된다. 
// 그러므로 각 원소들을 모두 루트이고, parent로 자기자신을 참조한다.

// Find
// 어떤 원소가 속한 집합을 알기 위해, 해당 원소의 루트 번호를 찾는다.
// parent 배열을 거슬러 올라가면 루트 번호에 도달하게 된다.

// Union
// 어떤 두 원소를 합치기 위해,
// 두 원소가 속한 두 집합의 루트 번호를 찾고,
// 두 집합이 서로 다른 집합이라면 (루트 번호가 다르다면),
// 한쪽 루트가 다른쪽 루트를 부모로 참조한다. 
// 그러면 집합이 합쳐진다.

#include <iostream>
#include <vector>
using namespace std;

struct UnionFind
{
    vector<int> parent;

    UnionFind(int n) : parent(n)
    {
        // 모든 원소들은 자기자신을 부모로 갖는다.
        // 즉, 각각이 하나의 유일한 집합의 루트가 된다.
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    // i가 속한 집합의 루트 번호
    int Find(int i) const
    {
        if (i == parent[i]) return i;
        return Find(parent[i]);
    }

    // 두 집합 a, b를 합친다.
    void Union(int a, int b)
    {
        int root1 = Find(a);
        int root2 = Find(b);

        if (root1 == root2)
            return;

        parent[root1] = root2;
    }
};


int main()
{
    const int N = 10;
    UnionFind uf(N);

    uf.Union(1, 3);
    uf.Union(3, 5);
    uf.Union(6, 7);
    uf.Union(6, 9);
    uf.Union(1, 6);

    for (int i = 0; i < N; ++i)
    {
        cout << i << " " << uf.Find(i) << endl;
    }

    return 0;
}