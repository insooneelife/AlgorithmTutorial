// 완주하지 못한 선수
// https://programmers.co.kr/learn/courses/30/lessons/42576

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(vector<string> participant, vector<string> completion) 
{
    sort(begin(participant), end(participant));
    sort(begin(completion), end(completion));

    for (int i = 0; i < completion.size(); ++i)
    {
        if (participant[i] != completion[i])
        {
            return participant[i];
        }
    }

    return participant[participant.size() - 1];
}