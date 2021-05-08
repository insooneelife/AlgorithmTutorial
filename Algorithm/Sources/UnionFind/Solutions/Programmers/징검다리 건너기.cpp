
// 징검다리 건너기 (힙 & Union-Find)
// https://programmers.co.kr/learn/courses/30/lessons/64062


// 시행착오
// 1. 인풋이 1개인 케이스
// 2. 카운트를 체크하고 laststone을 갱신하는 순간은 Union 이후에만 가능한것은 아니다. (AddCount 이후에도 가능)
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Print.h"
using namespace std;

struct UnionFind
{
    vector<int> parent;
    vector<int> rank;
    vector<int> cnts;

    // 모든 트리의 높이 (rank)는 1로 초기화
    UnionFind(int n) : parent(n), rank(n, 1), cnts(n, 0)
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
        return parent[i] = Find(parent[i]);
    }

    // 두 집합 a, b를 합친다.
    void Union(int a, int b)
    {
        int root1 = Find(a);
        int root2 = Find(b);

        if (root1 == root2)
            return;

        int count1 = cnts[root1];
        int count2 = cnts[root2];

        if (rank[root1] > rank[root2]) swap(root1, root2);

        // 이제 rank[root2]가 rank[root1]보다 크거나 같으므로 root1을 root2의 자식으로 붙인다.
        parent[root1] = root2;
        cnts[root1] = count1 + count2;
        cnts[root2] = count1 + count2;
        
        // 트리의 높이가 같았었다면, 합친 후의 높이는 1 증가한다.
        if (rank[root1] == rank[root2]) ++rank[root2];
    }

    void AddCount(int i)
    {
        int root = Find(i);
        cnts[root]++;
    }

    int GetCount(int i)
    {
        int root = Find(i);
        return cnts[root];
    }
};

bool InRange(int n, int index)
{
    return 0 <= index && index < n;
}

int solution(vector<int> stones, int k) 
{
    using ii = pair<int, int>;

    UnionFind uf(stones.size());
    priority_queue<ii, vector<ii>, greater<ii>> pq;

    int answer = 0;
    int laststone = 0;

    for (int i = 0; i < stones.size(); ++i)
    {
        pq.push(make_pair(stones[i], i));
    }

    while (!pq.empty())
    {
        auto p = pq.top();
        int stone = p.first;
        int index = p.second;

        if (laststone != 0 && laststone != stone)
        {
            break;
        }

        uf.AddCount(index);
        vector<int> left_right = { index - 1, index + 1 };

        for (int lr : left_right)
        {
            if (InRange(stones.size(), lr) && uf.GetCount(lr) > 0)
            {
                uf.Union(lr, index);
            }
        }

        int cnt = uf.GetCount(index);
        if (cnt >= k)
        {
            laststone = stone;
            answer = laststone;
        }
        pq.pop();
    }

    return answer;
}


