// ����

// ���� ����1
// ����Լ��� ���� �˰��� ����




















#include <iostream>
#include <vector>
#include "STL.h"
#include "Utility.h"
#include "Algorithm.h"

using namespace std;

const int N = 4;
const int K = 2;

// current�� 1���� K���� �̵����Ѻ��� ���� or ����x 
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

    // ����
    combs.push_back(current);
    Comb1(current + 1, combs);
    combs.pop_back();

    // ���� x
    Comb1(current + 1, combs);
}

// 1���� N������ �ϳ��� �����غ�.
// i1 ������ ���,
// i1 + 1���� N������ �ϳ��� �����غ�. 
// i2 ������ ���,
// i2 + 1���� N������ �ϳ��� �����غ�. 
// i3 ������ ��� ...
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