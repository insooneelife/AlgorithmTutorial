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

    if (current > N)
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


// �ݺ������ε� ���� �����ϴ�.
void Comb3(int n, int k)
{
    vector<int> choice(k);
    for (int i = 0; i < k; i++)
    {
        choice[i] = i;
    }

    while (choice[k - 1] < n)
    {
        Print::Container(choice);

        int t = k - 1;
        // �ִ밪�� �������� ���� ���� ������ ���Ҹ� ã��
        while (t != 0 && choice[t] == n - k + t)
        {
            t--;
        }

        // �ش� ���Ҹ� ����
        choice[t]++;

        // �ش� ���� ���� ��� ���� ����
        for (int i = t + 1; i < k; i++)
        {
            choice[i] = choice[i - 1] + 1;
        }
    }
}

int main()
{
    vector<int> combs;
    //Comb1(1, combs);
    //Comb2(N, K, combs);
    //Comb3(N, K);

    /*
    vector<vector<int>> all_combs;
    Algorithm::CombinationsIterate(5, 3, all_combs);
    for (int i = 0; i < all_combs.size(); ++i)
    {
        Print::Container(all_combs[i]);
    }
    */

    return 0;
}