
// 최적의 행렬 곱셈 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12942

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