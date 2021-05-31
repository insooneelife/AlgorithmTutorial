
// 보석 쇼핑 (탐욕법)
// https://programmers.co.kr/learn/courses/30/lessons/67258

// 시행착오
// 1. unsigned int인 size를 -1값인 right와 비교하니 right가 더 크다고 판단.

// 문제풀이
// 보석 전체집합 U = { all }
// 현재 보석집합 S = {}
// 오른쪽 인덱스 right와 왼쪽 인덱스 left로 최소구간을 표현한다.

// S == U 일 때까지, right++
// S == U 인 동안, left++, 최소구간 갱신
// 위 과정 반복


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

struct MinData
{
    void Update(int m, int l, int r)
    {
        if (minv > m)
        {
            minv = m;
            left = l;
            right = r;
        }
    }

    int minv;
    int left;
    int right;
};

vector<int> solution(vector<string> gems)
{
    const set<string> U(begin(gems), end(gems));
    const int gemsize = gems.size();
    map<string, int> S;

    MinData mindata = { numeric_limits<int>::max(), 0, 0 };
    int right = -1;
    int left = 0;
    int prev_left = 0;

    while (true)
    {
        while (S.size() < U.size() && right < gemsize - 1)
        {
            right++;
            S[gems[right]]++;
        }

        while (S.size() == U.size() && left <= right)
        {
            mindata.Update(right - left + 1, left, right);
            S[gems[left]]--;
            if (S[gems[left]] == 0)
            {
                S.erase(gems[left]);
            }
            left++;
        }

        if (left == prev_left)
            break;

        prev_left = left;
    }

    return { mindata.left + 1, mindata.right + 1 };
}

int main()
{
    vector<string> gems = { "DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA" };
    vector<int> v = solution(gems);
    cout << v[0] << " " << v[1] << endl;

    return 0;
}