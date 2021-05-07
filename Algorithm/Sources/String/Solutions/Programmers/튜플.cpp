
// 튜플 (문자열)
// https://programmers.co.kr/learn/courses/30/lessons/64065

// 시행착오
// 1. 문자열의 원소집합들이 개수 순서대로 정렬되어 있어야 현재집합 - 이전집합 연산이 가능하다.

#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>
#include "Print.h"

using namespace std;

static std::vector<std::string> Split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(str);
    while (std::getline(token_stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> SplitSets(const std::string& str)
{
    vector<string> splits;
    string temp = "";
    bool open = false;

    for (auto c : str)
    {
        if (c == '{')
        {
            temp = "";
            open = true;
        }
        else if (c == '}')
        {
            splits.push_back(temp);
            open = false;
        }
        else
        {
            if(open)
                temp.push_back(c);
        }
    }

    return splits;
}


vector<int> solution(string s) 
{
    vector<int> answer;
    string setstr = s.substr(1, s.size() - 2);
    vector<string> sets = SplitSets(setstr);
    vector<vector<string>> all;

    for (auto str : sets)
    {
        vector<string> elems = Split(str, ',');
        all.push_back(elems);
    }

    sort(begin(all), end(all), [](const vector<string>& a, const vector<string>& b) { return a.size() < b.size(); });

    vector<string> prev_elems;
    for (auto elems : all)
    {
        vector<string> output;
        sort(begin(elems), end(elems));
        set_difference(begin(elems), end(elems), begin(prev_elems), end(prev_elems), back_inserter(output));

        answer.push_back(stoi(output[0]));
        prev_elems = elems;
    }

    return answer;
}


int main()
{
    //string s = "{{2},{2,1},{2,1,3},{2,1,3,4}}";
    string s = "{{1,2,3},{2,1},{1,2,4,3},{2}}";
    //string s = "{{123}}";


    vector<int> answer = solution(s);

    Print::Container(answer);

    return 0;
}