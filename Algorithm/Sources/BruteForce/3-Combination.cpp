// 조합

// 조합 예제1
// 재귀함수로 조합 알고리즘 구현




















#include <iostream>
#include <vector>
#include "STL.h"
#include "Utility.h"
#include "Algorithm.h"

using namespace std;

const int N = 4;
const int K = 2;

// current를 1부터 K까지 이동시켜보며 선택 or 선택x 
void Comb1(int current, std::vector<int>& combs)
{
    if (combs.size() == K)
    {
        Print::Container(combs);
        return;
    }

    if (current > K)
    {
        return;
    }

    // 선택
    combs.push_back(current);
    Comb1(current + 1, combs);
    combs.pop_back();

    // 선택 x
    Comb1(current + 1, combs);
}

// 1부터 N까지를 하나씩 선택해봄.
// i1 선택인 경우,
// i1 + 1부터 N까지를 하나씩 선택해봄. 
// i2 선택인 경우,
// i2 + 1부터 N까지를 하나씩 선택해봄. 
// i3 선택인 경우 ...
// ...
void Comb2(int n, int pick, vector<int>& combs)
{
    if (pick == 0)
    {
        Print::Container(combs);
        return;
    }

    int start = combs.size() > 0 ? combs.back() + 1 : 1;
    for (int i = start; i <= n; ++i)
    {
        combs.push_back(i);
        Comb2(n, pick - 1, combs);
        combs.pop_back();
    }
}

int main()
{
    vector<int> combs;
    Comb2(N, K, combs);

    return 0;
}