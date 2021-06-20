
// Partial Sum
// 부분합, 구간합

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

// 구간합
long long RangeSum(const vector<long long>& psum, int from, int to)
{
    if (from == 0) return psum[to];
    return psum[to] - psum[from - 1];
}

// 일반 방법
void PartialSum(const vector<int>& v)
{
    vector<long long> psum(v.size());
    for (int i = 1; i < psum.size(); ++i)
        psum[i] = psum[i - 1] + v[i];

    cout << RangeSum(psum, 1, 3) << endl;
}

// stl 이용
void PartialSumSTL(const vector<int>& v)
{
    vector<long long> psum(v.size());
    partial_sum(begin(v), end(v), begin(psum));
    cout << RangeSum(psum, 1, 3) << endl;
}

int main()
{
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    PartialSum(v);
    PartialSumSTL(v);

    return 0;
}

// 연습 문제 1.
// 구간 합 구하기 4
// https://www.acmicpc.net/problem/11659