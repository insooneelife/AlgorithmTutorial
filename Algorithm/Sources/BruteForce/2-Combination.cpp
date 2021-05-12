// ����

// ���� ���� 1.
// ����Լ��� ���� �˰��� ����


// ���� ����
// �޴� ������ (����)
// https://programmers.co.kr/learn/courses/30/lessons/72411
















#include <iostream>
#include <vector>
#include "STL.h"
#include "Utility.h"
#include "Algorithm.h"

using namespace std;

const int N = 4;
const int K = 2;


// 1���� N������ �ϳ��� �����غ�.
// i1 ������ ���,
// i1 + 1���� N������ �ϳ��� �����غ�. 
// i2 ������ ���,
// i2 + 1���� N������ �ϳ��� �����غ�. 
// i3 ������ ��� ...
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

// �������̽� �Լ�
void Comb1(int n, int k)
{
    vector<int> combs;
    Comb1(n, k, combs);
}


// �ݺ������ε� ���� �����ϴ�.
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

// ��� �κ�����
// ��� k�� ���� ������ ��ģ��.
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


    // ��� ����
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