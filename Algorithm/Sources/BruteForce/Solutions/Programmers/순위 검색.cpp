// 순위 검색 (조합 or bitmask and 해시)
// https://programmers.co.kr/learn/courses/30/lessons/72412


#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <bitset>
#include "Utility.h"

using namespace std;

vector<int> solution(vector<string> info, vector<string> query)
{
    vector<int> answer;
    map<string, map<string, map<string, map<string, vector<int>>>>> table;
    string lang;
    string job;
    string career;
    string food;
    string tmp;
    int check_score;

    for (auto e : info)
    {
        istringstream iss(e);
        iss >> lang >> job >> career >> food >> check_score;

        vector<string> input = { lang, job, career, food };

        for (int i = 0; i < 16; ++i)
        {
            bitset<4> bit(i);
            vector<string> made(4);

            for (int b = 0; b < 4; ++b)
            {
                bit[b] ? made[b] = input[b] : made[b] = "-";
            }

            table[made[0]][made[1]][made[2]][made[3]].push_back(check_score);
        }
    }

    for (auto q : query)
    {
        istringstream iss(q);
        iss >> lang >> tmp >> job >> tmp >> career >> tmp >> food >> check_score;

        const vector<int>& scores = table[lang][job][career][food];

        int cnt = 0;
        for (auto s : scores)
        {
            if (check_score <= s)
            {
                cnt++;
            }
        }
        answer.push_back(cnt);
    }

    return answer;
}


int main()
{
    vector<string> info =
    {
        "java backend junior pizza 150",
        "python frontend senior chicken 210",
        "python frontend senior chicken 150",
        "cpp backend senior pizza 260",
        "java backend junior chicken 80",
        "python backend senior chicken 50"
    };

    vector<string> query =
    {
        "java and backend and junior and pizza 100",
        "python and frontend and senior and chicken 200",
        "cpp and - and senior and pizza 250",
        "- and backend and senior and - 150",
        "- and - and - and chicken 100",
        "- and - and - and - 150"
    };

    vector<int> answer = solution(info, query);

    Print::Container(answer);

    return 0;
}