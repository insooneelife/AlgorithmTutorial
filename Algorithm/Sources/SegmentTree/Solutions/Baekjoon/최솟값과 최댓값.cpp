
// 최솟값과 최댓값
// https://www.acmicpc.net/problem/2357


// 시행착오
// 1. cout을 하면 시간초과가 뜬다. 
// 다음 코드를 추가하여도 시간초과가 뜬다. printf로 대체
// ios_base::sync_with_stdio(false);
// cin.tie(NULL);
// cout.tie(NULL);



#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
using namespace std;

struct MinSegmentTree 
{
    MinSegmentTree(const vector<int>& v) : N (v.size()), tree(4 * N)
    {
        Init(v, 1, 0, N - 1);
    }

    int Init(const vector<int>& v, int node, int from, int to)
    {
        if (from == to)  
            return tree[node] = v[from];

        int mid = (from + to) / 2;
        int left_min = Init(v, node * 2, from, mid);
        int right_min = Init(v, node * 2 + 1, mid + 1, to);
        return tree[node] = min(left_min, right_min);
    }

    // query range [qfrom, qto]
    int Query(int qfrom, int qto) 
    {
        return Query(1, qfrom, qto, 0, N - 1);
    }

    // query range [qfrom, qto]
    // boundary range [from, to]
    int Query(int root, int qfrom, int qto, int from, int to)
    {
        if (qto < from || to < qfrom)
        {
            return numeric_limits<int>::max();
        }
        else if (qfrom <= from && to <= qto)
        {
            return tree[root];
        }
        else 
        {
            int mid = (from + to) / 2;
            int left_min = Query(2 * root, qfrom, qto, from, mid);
            int right_min = Query(2 * root + 1, qfrom, qto, mid + 1, to);
            return min(left_min, right_min);
        }
    }

private:
    const int N;

    // tree saves min value of each ranges
    vector<int> tree;
};


int main() 
{
    int n, m;
    cin >> n >> m;

    vector<int> inputs(n);
    vector<int> ninputs(n);
    vector< pair<int, int> > range(m);

    for (int i = 0; i < n; i++) 
    {
        cin >> inputs[i];
        ninputs[i] = -inputs[i];
    }

    MinSegmentTree mintree(inputs);
    MinSegmentTree maxtree(ninputs);

    for (int i = 0; i < m; i++) 
    {
        int a, b;
        cin >> a >> b;
        range[i] = make_pair(a - 1, b - 1);
    }

    for (auto e : range) 
    {
        int minv = mintree.Query(e.first, e.second);
        int maxv = -maxtree.Query(e.first, e.second);
        printf("%d %d\n", minv, maxv);
    }

    return 0;
}