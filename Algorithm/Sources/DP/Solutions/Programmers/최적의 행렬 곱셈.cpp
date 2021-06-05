
// 최적의 행렬 곱셈 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12942

// 첫번째 방법
// A[5, 3], B[3, 10], C[10, 6]
// AB = 5 * 3 * 10 = 150 (연산 횟수)
// 5 * 10 (새로운 행렬 AB)
// (AB)C = 150 + 5 * 10 * 6 = 150 + 300 = 450

// 두번째 방법
// BC = 3 * 10 * 6 = 180 (연산 횟수)
// 3 * 6 (새로운 행렬 BC)
// A(BC) = 180 + 5 * 3 * 6 = 180 + 90 = 270


// 행렬 {A, B, C, D}의 곱 ABCD가 있을 때,

// 5가지 경우의 수
// A(B(CD))
// A((BC)D)
// (AB)(CD)
// (A(BC))D
// (AB)C)D

// 괄호치기 문제의 점화식

// 0123
// ABCD 를 인덱스 k 를 기준으로 쪼갠다.

// k = 0 인 경우,
// A(BCD)

// k = 1 인 경우,
// (AB)(CD)

// k = 2 인 경우,
// (ABC)D


// 쪼개진 부분들을 재귀적으로 다시 쪼갠다.
// BCD를 인덱스 k를 기준으로 쪼갠다.

// k = 0 인 경우,
// B(CD)

// k = 1 인 경우,
// (BC)D


// 점화식
// F(i, j) : i 위치의 행렬부터 j 위치의 행렬까지의 최소곱셈수

// min(for all k: F(i, k)(최소곱셈수) + F(k + 1, j)(최소곱셈수) + 두 부분 행렬의 곱셈수) 
// k 범위 [i, j - 1]



#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <functional>
using namespace std;
using ll = long long;

struct Data
{
    ll r, c, sum;
};

Data mem[202][202] = { 0 };
bool visited[202][202] = { false };

// A[5, 3]  B[3, 10]
// AB[5, 10], 5 * 3 * 10

Data MulMatrix(const Data& a, const Data& b)
{
    return { a.r, b.c, a.sum + b.sum + a.r * a.c * b.c };
}

Data F(const vector<Data>& matrixs, int i, int j)
{
    if (j - i == 0)
        return matrixs[i];

    if (j - i == 1)
        return MulMatrix(matrixs[i], matrixs[j]);

    if (visited[i][j])
        return mem[i][j];

    ll minv = numeric_limits <ll>::max();
    Data minmat;
    for (int k = i; k < j; ++k)
    {
        Data left = F(matrixs, i, k);
        Data right = F(matrixs, k + 1, j);
        Data ret = MulMatrix(left, right);

        if (minv > ret.sum)
        {
            minv = ret.sum;
            minmat = ret;
        }
    }

    visited[i][j] = true;
    return mem[i][j] = minmat;
}


int solution(vector<vector<int>> matrix_sizes)
{
    vector<Data> matrixs;
    matrixs.reserve(matrix_sizes.size());
    for (const vector<int>& m : matrix_sizes)
    {
        matrixs.push_back({ m[0], m[1], 0 });
    }

    return F(matrixs, 0, matrixs.size() - 1).sum;
}


int main()
{
    vector<vector<int>> matrix_sizes = { {5, 3}, {3, 10}, {10, 6} };
    cout << solution(matrix_sizes) << endl;

    return 0;
}