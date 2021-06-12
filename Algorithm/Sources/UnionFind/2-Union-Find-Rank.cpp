// 상호 배타적 집합
// 랭크를 이용한 Union 최적화 구현

// 트리를 이용하여 자료구조를 설계하면 O(logN)의 성능으로 Find와 Union이 둘 다 가능하다.
// 하지만 이 성능은 트리가 균형잡혀 있을경우에만 해당된다.
// 만약 트리가 한쪽으로 완전하게 치우쳐져 있다면, 배열과 크게 다를것이 없을 것이다.
// 이 문제를 피하기 위해, 
// 트리의 높이를 비교하여 낮은쪽 트리를 높은쪽 트리에 붙이는 전략을 사용할 수 있다.
// 이러한 전략을 랭크에 의한 합치기(Union by Rank)라고 부른다.


#include <iostream>
#include <vector>
using namespace std;

struct RankedUnionFind
{
    vector<int> parent;
    vector<int> rank;

    // 모든 트리의 높이 (rank)는 1로 초기화
    RankedUnionFind(int n) : parent(n), rank(n, 1)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    // i가 속한 집합의 루트 번호
    int Find(int i)
    {
        if (i == parent[i]) return i;
        
        // 경로 압축을 이용한 최적화
        return parent[i] = Find(parent[i]);
    }

    // 두 집합 a, b를 합친다.
    void Union(int a, int b)
    {
        int root1 = Find(a);
        int root2 = Find(b);

        if (root1 == root2)
            return;

        if (rank[root1] > rank[root2]) swap(root1, root2);
        // 이제 rank[root2]가 rank[root1]보다 크거나 같으므로 root1을 root2의 자식으로 붙인다.
        parent[root1] = root2;

        // 트리의 높이가 같았었다면, 합친 후의 높이는 1 증가한다.
        if (rank[root1] == rank[root2]) ++rank[root2];
    }
};


int main()
{
    const int N = 10;
    RankedUnionFind uf(N);

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


// 직접 구현해보기

// 연습 문제
// 섬 연결하기
// https://algorfati.tistory.com/126