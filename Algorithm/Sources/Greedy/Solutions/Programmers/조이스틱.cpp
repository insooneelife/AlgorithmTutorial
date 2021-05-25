
// 시행착오
// 1. 이미 지나간 곳을 다시 지나가는게 나은 경우

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(string name) 
{
    int counts[26] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int len = name.length();

    // forward or backward
    int min_dis = len - 1;

    for (int i = 0; i < len; ++i) 
    {
        int ni = i + 1;
        while (ni < len && name[ni] == 'A')
        {
            ni++;
        }

        int forward = i;
        int backward = len - ni;

        // (forward, ~forward, backward) or (backward, ~backward, forward)
        min_dis = min(min_dis, forward + backward + min(forward, backward));
    }

    int answer = 0;
    answer += min_dis;

    for (auto c : name)
        answer += counts[c - 'A'];

    return answer;
}

int main()
{
    string name = "ZZAAZZ";

    int answer = solution(name);
    cout << answer << endl;

    return 0;
}

