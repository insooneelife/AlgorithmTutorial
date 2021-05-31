
// 단속카메라 (탐욕법)
// https://programmers.co.kr/learn/courses/30/lessons/42884

// 시행착오
// 1. 다음 코드 수정 - 이 코드는 delta가 연속적으로 음수인 경우에도 prev_idx값을 변경시켜서 문제를 일으킴
// 수정 전, prev_idx = idx;
// 수정 후, max_idx = max(max_idx, idx);

// 문제 풀이
// 입장시간 기준 오름차순 정렬 (인덱스를 만들기 위함이다)
// {입장시간, 1, 인덱스}, {퇴장시간, -1, 인덱스} 를 모두 포함한 컨테이너를 시간 기준으로 정렬한다.
// 정렬된 데이터의 delta를 읽다보면, 음수가 나오게 되는데, 
// 이때가 해당 차량을 검사할 수 있는 마지막 위치이면서 동시에 최대로 검사할 수 있는 위치이다. (이 시점에 cnt 증가)
// 이미 검사된 차량들의 퇴장데이터는 건너뛰어야 하므로, 마지막 최대 인덱스를 저장하여 해당 인덱스보다 높은 경우만 검사하도록 한다.


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Data
{
    int val;
    int delta;
    int idx;
};

int solution(vector<vector<int>> routes)
{
    sort(begin(routes), end(routes), [](const vector<int>& a, const vector<int>& b)
        {
            return a[0] < b[0];
        });

    vector<Data> access;
    access.reserve(routes.size() * 2);

    for (int i = 0; i < routes.size(); ++i)
    {
        int enter = routes[i][0];
        int exit = routes[i][1];

        access.push_back({ enter, 1, i });
        access.push_back({ exit, -1, i });
    }

    sort(begin(access), end(access), [](const Data& a, const Data& b)
        {
            if (a.val == b.val)
                return a.idx > b.idx;
            return a.val < b.val;
        });

    int cnt = 0;
    int max_idx = 0;
    int alive_idx = 0;

    for (int i = 0; i < access.size(); ++i)
    {
        int delta = access[i].delta;
        int idx = access[i].idx;

        if (delta < 0)
        {
            if (idx >= alive_idx)
            {
                cnt++;
                alive_idx = max_idx + 1;
            }
        }
        max_idx = max(max_idx, idx);
    }

    return cnt;
}

int main()
{
    vector<vector<int>> routes = { {-20, 15} ,{-14, -5},{-18, -13},{-5, -3} };
    cout << solution(routes) << endl;

    return 0;
}