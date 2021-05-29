
// 징검다리 건너기
// https://programmers.co.kr/learn/courses/30/lessons/64062

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 징검다리를 건너본다.
bool Try(const vector<int>& stones, const int k, int number)
{
    int cnt = 0;
    for (int i = 0; i < stones.size(); ++i)
    {
        if (stones[i] - number <= 0)
        {
            cnt++;
            if (cnt == k)
                return false;
        }
        else
        {
            cnt = 0;
        }
    }
    return true;
}

// 건너가는 회수를 탐색 대상으로 잡고 이분탐색을 수행한다.
// 건너가는 회수 범위 [0, 200000000] 
int Search(const vector<int>& stones, const int k, int from, int to)
{
    if (from >= to)
        return from;

    int mid = (from + to) / 2;

    if (Try(stones, k, mid))
        return Search(stones, k, mid + 1, to);
    else
        return Search(stones, k, from, mid);
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

    cout << solution(stones, k);

    return 0;
}

