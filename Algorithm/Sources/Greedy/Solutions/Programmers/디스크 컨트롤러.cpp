
// 디스크 컨트롤러 (힙)
// https://programmers.co.kr/learn/courses/30/lessons/42627

// 시행착오
// 1. 하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다.
// 위 조건으로 인해 문제 설계가 굉장히 많이 변하게 된다.

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;


struct Data
{
    int start;
    int length;

    bool operator<(const Data& other) const
    {
        return length < other.length;
    }

    bool operator>(const Data& other) const
    {
        return length > other.length;
    }
};

int solution(vector<vector<int>> jobs) 
{
    priority_queue<Data, vector<Data>, greater<Data>> pq;

    sort(begin(jobs), end(jobs));

    int i = 0;
    int time = 0;
    int sum = 0;
    while (i < jobs.size() || !pq.empty()) 
    {
        if (jobs.size() > i && time >= jobs[i][0]) 
        {
            pq.push({ jobs[i][0], jobs[i][1] });
            i++;
            continue;
        }
        if (!pq.empty()) 
        {
            Data top = pq.top();
            time += top.length;
            sum += time - top.start;
            pq.pop();
        }
        else
        {
            time = jobs[i][0];
        }
    }

    return sum / jobs.size();
}

int main()
{
    vector<vector<int>> jobs = { {0, 3}, {1, 9}, {2, 6} };
    //vector<vector<int>> jobs = { {0, 3}, {2, 7}, {6, 2} }; // 17
    //vector<vector<int>> jobs = { {0, 3}, {4, 2}, {2, 7} }; // 16
    //vector<vector<int>> jobs = { {0, 3}, {3, 2}, {2, 7} }; // 15

    cout << solution(jobs);

    return 0;
}


