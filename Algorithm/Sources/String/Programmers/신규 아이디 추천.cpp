// 신규 아이디 추천 (문자열 기본)
// https://programmers.co.kr/learn/courses/30/lessons/72410

#include <string>
#include <vector>
#include <iostream>

using namespace std;

void transform1(string& new_id)
{
    for (int i = 0; i < new_id.size(); ++i)
    {
        if ('A' <= new_id[i] && new_id[i] <= 'Z')
        {
            new_id[i] = new_id[i] - 'A' + 'a';
        }
    }
}

string transform2(const string& new_id)
{
    string out = "";

    for (int i = 0; i < new_id.size(); ++i)
    {
        char c = new_id[i];
        if ('a' <= c && c <= 'z' || '0' <= c && c <= '9' || c == '-' || c == '_' || c == '.')
        {
            out += c;
        }
    }
    return out;
}

string transform3(const string& new_id)
{
    string out = "";

    bool flag = false;
    for (int i = 0; i < new_id.size(); ++i)
    {
        char c = new_id[i];
        if (c == '.')
        {
            if (!flag)
            {
                out += c;
            }

            flag = true;
        }
        else
        {
            out += c;
            flag = false;
        }
    }
    return out;
}

void transform4(string& new_id)
{
    if (new_id.size() > 0)
    {
        if (new_id[0] == '.')
        {
            new_id.erase(std::begin(new_id));
        }
    }

    if (new_id.size() > 0)
    {
        if (new_id[new_id.size() - 1] == '.')
        {
            new_id.pop_back();
        }
    }
}

void transform5(string& new_id)
{
    if (new_id == "")
    {
        new_id.push_back('a');
    }
}

void transform6(string& new_id)
{
    while (new_id.size() > 15)
    {
        new_id.pop_back();
    }

    if (new_id.size() > 0)
    {
        if (new_id[new_id.size() - 1] == '.')
        {
            new_id.pop_back();
        }
    }
}

void transform7(string& new_id)
{
    if (new_id.size() <= 2)
    {
        char last = new_id[new_id.size() - 1];
        while (new_id.size() < 3)
        {
            new_id.push_back(last);
        }
    }
}

string solution(string new_id) {

    cout << new_id << endl;
    transform1(new_id);
    cout << new_id << endl;
    new_id = transform2(new_id);
    cout << new_id << endl;
    new_id = transform3(new_id);
    cout << new_id << endl;
    transform4(new_id);
    cout << new_id << endl;
    transform5(new_id);
    cout << new_id << endl;
    transform6(new_id);
    cout << new_id << endl;
    transform7(new_id);

    return new_id;
}













