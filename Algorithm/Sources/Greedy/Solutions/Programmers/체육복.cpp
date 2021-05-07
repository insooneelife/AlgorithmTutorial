
// 체육복
// https://programmers.co.kr/learn/courses/30/lessons/42862

// 시행착오
// 1. 도난당한 학생 중 여분 체육복이 있는 학생은 다른 학생에게 빌려줄 수 없으므로, 미리 케이스에서 제거하고 시작해야한다.

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include "Print.h"

using namespace std;

bool FindTwoWay(int first, int second, set<int>& reserves)
{
    auto it = reserves.find(first);
    if (it != end(reserves))
    {
        reserves.erase(it);
        return true;
    }
    else
    {
        it = reserves.find(second);
        if (it != end(reserves))
        {
            reserves.erase(it);
            return true;
        }
        else
        {
            int mid = (first + second) / 2;
            it = reserves.find(mid);
            if (it != end(reserves))
            {
                reserves.erase(it);
                return true;
            }
        }
    }
    return false;
}

int solution(int n, vector<int> lost, vector<int> reserve) 
{
    sort(begin(lost), end(lost));
    sort(begin(reserve), end(reserve));

    vector<int> output_lost;
    vector<int> output_reserve;
    set_difference(begin(lost), end(lost), begin(reserve), end(reserve), back_inserter(output_lost));
    set_difference(begin(reserve), end(reserve), begin(lost), end(lost), back_inserter(output_reserve));

    lost = output_lost;
    set<int> reserves(begin(output_reserve), end(output_reserve));

    int left = 0;
    int right = lost.size() - 1;
    int lostN = lost.size();
    int cnt = 0;

    while (true)
    {
        if (left > right)
        {
            break;
        }
        else if (left == right)
        {
            if (FindTwoWay(lost[left] - 1, lost[left] + 1, reserves))
            {
                cnt++;
            }
        }
        else
        {
            if (FindTwoWay(lost[left] - 1, lost[left] + 1, reserves))
            {
                cnt++;
            }

            if (FindTwoWay(lost[right] + 1, lost[right] - 1, reserves))
            {
                cnt++;
            }
        }

        left++;
        right--;
    }

    return n - (lostN - cnt);
}

int main()
{
    int n = 5;
    vector<int> lost = { 2, 3, 4 };
    vector<int> reserve = { 1, 2, 3 };

    cout << solution(n, lost, reserve);

    return 0;
}