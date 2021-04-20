// 순위 검색 (조합 + 해시)
// https://programmers.co.kr/learn/courses/30/lessons/72412

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

const vector<vector<string>> param{ { "-", "cpp", "java", "python" }, { "-", "backend", "frontend" }, { "-", "junior", "senior" }, { "-", "chicken", "pizza" } };

void print(const vector<string>& container)
{
    for (auto e : container)
    {
        cout << e << " ";
    }
    cout << endl;
}

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

        for (auto l : param[0])
        {
            if (!(l == "-" || lang == l))
                continue;

            for (auto j : param[1])
            {
                if (!(j == "-" || job == j))
                    continue;

                for (auto c : param[2])
                {
                    if (!(c == "-" || career == c))
                        continue;

                    for (auto f : param[3])
                    {
                        if (!(f == "-" || food == f))
                            continue;

                        table[l][j][c][f].push_back(check_score);
                    }
                }
            }
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
        //print(data);
    }

    return answer;
}