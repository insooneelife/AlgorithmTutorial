// 문자열 압축
// https://programmers.co.kr/learn/courses/30/lessons/60057

// 시행착오
// 1. 문자열을 무조건 제일 앞부터 잘라야 한다는 조건을 제대로 읽지 않았음.
// 2. 한번 자른 문자열이 계속 나타나는지 확인하는것이 아니라, 
//    고정된 크기로 자른 문자열이 연속적으로 같은지 판단해야하는데 이 부분을 잘못 이해함
// 3. 탐색 범위 (i < s.size() / 2) -> (i <= s.size() / 2)
// 4. 아무런 답도 얻지 못하는 경우 input의 길이를 반환해야함 (한 글자 예외처리 중 발견)


#include <iostream>
#include <string>
#include <vector>
//#include "Print.h"
using namespace std;

int Compress(const string& target, int size)
{
    int start = 0;
    int cnt = 0;
    vector<int> counts;
    string substr = target.substr(start, size);
    string prev = substr;

    while (true)
    {
        size_t i = target.find(substr, start);

        if (i == string::npos)
            break;
        
        if (prev == substr)
        {
            cnt++;
        }
        else
        {
            if (cnt > 1)
                counts.push_back(cnt);
            cnt = 1;
        }                      

        start = i + size;

        if (start >= target.size())
            break;

        prev = substr;
        substr = target.substr(start, size);
    }
    
    if (cnt > 1)
        counts.push_back(cnt);

    int sum = 0;
    for (auto c : counts)
    {
        int discount = (c - 1) * size - to_string(c).size();
        sum += discount;
    }
    int ret = target.size() - sum;
    //Print::Container(counts);
    return ret;
}

int solution(string s) 
{
    int answer = s.size();
    for (int i = 1; i <= s.size() / 2; ++i)
    {
        int cnt = Compress(s, i);
        answer = min(answer, cnt);
    }

    return answer;
}

int main()
{
    //string input = "a";
    //string input = "aabbaccc";
    //string input = "ababcdcdababcdcd";
    //string input = "abcabcdede";
    //string input = "aaaaaaaaaaaaaaaaaaaaaaa";
    //string input = "abcabcabcabcdededededede";
    string input = "xababcdcdababcdcd";

    int answer = solution(input);

    cout << "answer : "<< answer;

    return 0;
}