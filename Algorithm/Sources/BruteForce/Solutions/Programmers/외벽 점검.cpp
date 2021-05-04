// 외벽 점검 (완전탐색, 순열)
// https://programmers.co.kr/learn/courses/30/lessons/60062

// 문제 해결
// [모든 원형 외벽을 기준으로] * [dist의 모든 순열] * [순서대로 채울 수 있는만큼 채우기]
// 환형 자료구조로 효율성이 좋은 queue를 활용함
// 환형 문제에서 N-1 -> 0 으로 넘어가는 부분에서 생기는 예외를 피하기 위해, weak[i] 위치를 weak[i + 1] - weak[i] = 거리로 변환하여 활용함

// 시행착오
// cmath (pow 함수) 프로그래머스 런타임 에러
// 선택여부에 대한 조합은 필요가 없었음 (오히려 예외가 생김)
// 모든 외벽을 기준으로 할 필요가 있음
// 회전방향은 고려할 필요가 없었음 (CW 방향으로 가능한 케이스는 CCW 방향으로도 항상 가능하기 때문에 탐색공간을 축소시킬 수 있음)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <bitset>
#include <functional>
#include <sstream>
#include <cmath>
//#include "Print.h"

using namespace std;

int Selection(const vector<int>& weak_dist, const vector<int>& dist)
{
    int min_cnt = numeric_limits<int>::max();
    int weak_size = weak_dist.size();

    for(int rotate = 0; rotate < weak_size; ++rotate)
    {
        queue<int> que;
        vector<int> cdist = dist;
        int cnt = 0;

        for (int i = 0; i < weak_size; ++i)
        {
            que.push(weak_dist[(rotate + i) % weak_size]);
        }

        int i = 0;
        while (!que.empty() && i < cdist.size())
        {
            int weak_dis = que.front();

            if (cdist[i] >= weak_dis)
            {
                cdist[i] -= weak_dis;
                if (que.empty())
                {
                    cnt++;
                }
            }
            else
            {
                cnt++;
                i++;
            }
            que.pop();
        }

        if(que.empty())
        {
            min_cnt = min(min_cnt, cnt);
        }
    }

    return min_cnt;
}


int solution(int n, vector<int> weak, vector<int> dist) 
{
    vector<int> weak_dist;
    for (int i = 0; i < weak.size(); ++i)
    {
        if (i == weak.size() - 1)
        {
            weak_dist.push_back(n - weak[i] + weak[0]);
        }
        else
        {
            weak_dist.push_back(weak[i + 1] - weak[i]);
        }
    }

    sort(begin(dist), end(dist));
    int answer = numeric_limits<int>::max();

    do
    {
        //Print::Container(dist);
        int cnt = Selection(weak_dist, dist);
        answer = min(cnt, answer);


    } while (next_permutation(dist.begin(), dist.end()));

    return answer == numeric_limits<int>::max() ? -1 : answer;
}

int main()
{
    //int n = 12;
    //vector<int> weak = { 1, 5, 6, 10 };
    //vector<int> dist = { 1, 2, 3, 4 };

    //int n = 12;
    //vector<int> weak = { 1, 3, 4, 9, 10 };
    //vector<int> dist = { 3, 5, 7 };

    int n = 10;
    vector<int> weak = { 0, 5 };
    vector<int> dist = { 1 };

    int answer = solution(n, weak, dist);
    std::cout << answer ;

    return 0;
}