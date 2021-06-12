
// 최소 질의 구간트리

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
using namespace std;

struct MinSegmentTree
{
    MinSegmentTree(const vector<int>& v) : N(v.size()), tree(4 * N)
    {
        Init(v, 1, 0, N - 1);
    }

    // 구간트리의 초기화
    int Init(const vector<int>& v, int node, int from, int to)
    {
        if (from == to)
            return tree[node] = v[from];

        // 각 구간들의 최소값을 저장
        int mid = (from + to) / 2;
        int left_min = Init(v, node * 2, from, mid);
        int right_min = Init(v, node * 2 + 1, mid + 1, to);
        return tree[node] = min(left_min, right_min);
    }

    // 인터페이스 함수
    // query range [qfrom, qto]
    int Query(int qfrom, int qto)
    {
        return Query(1, qfrom, qto, 0, N - 1);
    }

    // 질의된 구간 내의 최소값을 구한다.
    // query range [qfrom, qto]
    // boundary range [from, to]
    int Query(int node, int qfrom, int qto, int from, int to)
    {
        // 구간이 겹치지 않는다면 매우 큰 값을 리턴 (이 값은 무시됨)
        if (qto < from || to < qfrom)
            return numeric_limits<int>::max();
        
        // 쿼리 구간에 분할 구간이 완전히 겹쳐진다면, 해당 구간의 최소값을 반환
        if (qfrom <= from && to <= qto)
            return tree[node];
        
        // 왼쪽 구간트리의 최소값, 오른쪽 구간트리의 최소값 중 최소값
        int mid = (from + to) / 2;
        int left_min = Query(2 * node, qfrom, qto, from, mid);
        int right_min = Query(2 * node + 1, qfrom, qto, mid + 1, to);
        return min(left_min, right_min);
    }

    // 구간트리의 특정 index 위치 값을 새로운 값으로 갱신한다.
    int Update(int node, int index, int newvalue, int from, int to)
    {
        // index가 구간에 포함되지 않는다면, 원래 값을 리턴 (이 값은 무시됨)
        if (index < from || to < index)
            return tree[node];

        // 트리의 리프에 도달 시, 값 갱신
        if (from == to)
            return tree[node] = newvalue;

        // 이 위치에 진입했다는 것은 구간에 index가 포함된다는 의미이다.
        // 재귀적으로 이 작업을 반복하고, 얻은 값을 통해 현재 구간을 갱신한다.
        int mid = (from + to) / 2;
        int left_min = Update(2 * node, index, newvalue, from, mid);
        int right_min = Update(2 * node + 1, index, newvalue, mid + 1, to);
        return tree[node] = min(left_min, right_min);
    }

private:
    const int N;

    // tree는 구간들을 표현하고, 각 구간의 최소값을 저장한다 (꽉 찬 이진트리)
    vector<int> tree;
};



// 구현해보기

// 연습문제
// 최솟값
// https://www.acmicpc.net/problem/10868