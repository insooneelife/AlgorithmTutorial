
// [3차] 압축
// https://programmers.co.kr/learn/courses/30/lessons/17684

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "Print.h"
using namespace std;

vector<int> solution(string msg)
{
    map<string, int> dict;
    for (int i = 0; i < 26; ++i)
        dict.insert(make_pair(string(1, (i + 'A')), dict.size() + 1));

    vector<int> answer;
    for (int i = 0; i < msg.size(); ++i)
    {
        for (int size = msg.size() - i; size >= 0; --size)
        {
            string sub = msg.substr(i, size);
            auto it = dict.find(sub);

            if (it != end(dict))
            {
                string add = sub + msg[i + size];
                dict.insert(make_pair(add, dict.size() + 1));
                i = i + size - 1;
                answer.push_back(it->second);
                break;
            }
        }
    }

    return answer;
}

int main()
{
    string msg = "KAKAO";
    vector<int> v = solution(msg);

    Print::Container(v);

    return 0;
}
