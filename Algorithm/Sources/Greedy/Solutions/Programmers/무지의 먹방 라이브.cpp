
// 무지의 먹방 라이브
// https://programmers.co.kr/learn/courses/30/lessons/42891

// 시행착오
// 1. prev_k - 1 을 할 필요가 없었음
// 2. k가 음수가 되며 중간에 루프가 중단되는 경우, pq의 원소들을 나열하여 k의 위치를 찾아주는 추가 코드가 필요함

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<int> food_times, long long k) 
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (int i = 0; i < food_times.size(); ++i)
    {
        int time = food_times[i]; 
        pq.push(make_pair(time, i + 1));
    }

    pair<int, int> top;
    pair<int, int> ptop;
    long long pk = k;

    while (!pq.empty())
    {
        ptop = top;
        top = pq.top();
        int mul = top.first - ptop.first;

        pk = k;
        k = k - pq.size() * mul;

        if (k < 0)
            break;

        pq.pop();
    }

    if (k >= 0)
    {
        return -1;
    }
    else
    {
        vector<pair<int, int>> v;
        while (!pq.empty())
        {
            v.push_back(pq.top());
            pq.pop();
        }

        sort(begin(v), end(v), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });
        int index = pk % v.size();
        int number = v[index].second;
        return number;
    }
}


int main()
{
    //long long k = 16;
    //vector<int> food_times = { 4, 2, 3, 6, 7, 1, 5, 8 };
    // answer = 3

    //long long k = 27;
    //vector<int> food_times = { 4,2,3,6,7,1,5,8 };
    // answer = 5

    long long k = 5;
    vector<int> food_times = { 3, 1, 2 };

    int answer = solution(food_times, k);
    cout << answer;

    return 0;
}