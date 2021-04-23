// 전화번호 목록 (해시 or 정렬)
// https://programmers.co.kr/learn/courses/30/lessons/42577


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool find(const string& a, const string& b)
{
    for (int i = 0; i < a.size() && i < b.size(); ++i)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

bool solution(vector<string> phone_book)
{
    bool answer = true;

    std::sort(std::begin(phone_book), std::end(phone_book));

    for (int i = 0; i < phone_book.size() - 1; ++i)
    {
        if (find(phone_book[i + 1], phone_book[i]))
        {
            return false;
        }
    }

    return true;
}