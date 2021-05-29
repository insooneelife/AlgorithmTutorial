
// 징검다리 건너기 (이분탐색)
// https://programmers.co.kr/learn/courses/30/lessons/64062

// 목표 변수 = 다리를 건너간 사람 수 [0, 200000000]

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int Search(const vector<int>& stones, int k, int start, int end)
{
    if (start >= end)
        return start;

    int mid = (start + end) / 2;
    int cnt = 0;
    bool success = true;

    for (int i = 0; i < stones.size(); ++i)
    {
        if (stones[i] - mid <= 0)
        {
            cnt++;
            if (cnt == k)
                success = false;
        }
        else
        {
            cnt = 0;
        }
    }

    if (success)
    {
        return Search(stones, k, mid + 1, end);
    }
    else
    {
        return Search(stones, k, start, mid);
    }
}

int solution(vector<int> stones, int k)
{
    int val = Search(stones, k, 0, 200000000);
    return val;
}

int main()
{
    vector<int> stones = { 2, 4, 5, 3, 2, 1, 4, 2, 5, 1 };
    int k = 3;

    //vector<int> stones = { 1 };
    //int k = 1;

    cout << solution(stones, k);

    return 0;
}

