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

    if (current > N)
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


// 반복문으로도 구현 가능하다.
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
        // 최대값에 도달하지 않은 가장 오른쪽 원소를 찾음
        while (t != 0 && choice[t] == n - k + t)
        {
            t--;
        }

        // 해당 원소를 증가
        choice[t]++;

        // 해당 원소 뒤의 모든 원소 증가
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