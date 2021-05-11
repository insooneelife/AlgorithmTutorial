// 조합

// 조합 예제 1.
// 재귀함수로 조합 알고리즘 구현


// 조합 문제
// 메뉴 리뉴얼 (조합)
// https://programmers.co.kr/learn/courses/30/lessons/72411
















#include <iostream>
#include <vector>
#include "STL.h"
#include "Utility.h"
#include "Algorithm.h"

using namespace std;

const int N = 4;
const int K = 2;


// 1부터 N까지를 하나씩 선택해봄.
// i1 선택인 경우,
// i1 + 1부터 N까지를 하나씩 선택해봄. 
// i2 선택인 경우,
// i2 + 1부터 N까지를 하나씩 선택해봄. 
// i3 선택인 경우 ...
// ...
void Comb1(int n, int k, vector<int>& combs)
{
    if (k == 0)
    {
        Print::Container(combs);
        return;
    }

    int start = combs.size() > 0 ? combs.back() + 1 : 1;
    for (int i = start; i <= n; ++i)
    {
        combs.push_back(i);
        Comb1(n, k - 1, combs);
        combs.pop_back();
    }
}

// 인터페이스 함수
void Comb1(int n, int k)
{
    vector<int> combs;
    Comb1(n, k, combs);
}


// 반복문으로도 구현 가능하다.
void Comb2(int n, int k)
{
    vector<int> choice(k);
    if (k == 0)
    {
        Print::Container(choice);
        return;
    }

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

// 모든 부분집합
// 모든 k에 대한 조합을 합친다.
void AllSubsets()
{
    vector<int> combs;
    for (int k = 0; k <= N; ++k)
    {
        Comb1(N, k);
    }
}

int main()
{
    vector<int> combs;
    //Comb1(1, combs);
    //Comb2(N, K, combs);
    //Comb3(N, K);

    //AllSubsets();


    // 사용 예제
    /*
    vector<string> company = { "Apple", "Google", "Amazon", "Facebook" };
    vector<vector<int>> all_combs;
    Algorithm::CombinationsIterate(company.size(), 2, all_combs);

    for (int i = 0; i < all_combs.size(); ++i)
    {
        for (int j = 0; j < all_combs[i].size(); ++j)
        {
            int index = all_combs[i][j];
            cout << company[index] << " ";
        }
        cout << endl;
    }
    */


    return 0;
}