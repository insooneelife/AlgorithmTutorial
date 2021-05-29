
// 구명보트 (탐욕법, 힙)
// https://programmers.co.kr/learn/courses/30/lessons/42885

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int solution(vector<int> people, int limit) 
{
    priority_queue<int, vector<int>, greater<>> small;
    priority_queue<int, vector<int>, less<>> big;
    sort(begin(people), end(people));
    int half = limit / 2;

    for (int i = 0; i < people.size(); ++i)
    {
        if (people[i] <= half)
            small.push(people[i]);
        else
            big.push(people[i]);
    }

    int cnt = 0;
    while (!small.empty() && !big.empty())
    {
        if (small.top() + big.top() <= limit)        
            small.pop();        

        cnt++;
        big.pop();
    }

    return (small.size() + 1) / 2 + big.size() + cnt;
}

int main()
{
    vector<int> people = { 70, 50, 80, 50 };
    int limit = 100;

    //vector<int> people = { 70, 80, 50};
    //int limit = 100;

    int ans = solution(people, limit);
    cout << ans << endl;

    return 0;
}
