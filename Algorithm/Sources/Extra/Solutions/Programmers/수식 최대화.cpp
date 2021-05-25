
// 수식 최대화
// https://programmers.co.kr/learn/courses/30/lessons/67257

#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>
//#include "Print.h"
using namespace std;
using ll = long long;

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

void Split(const std::string& str, const vector<string>& delimiters, int i, std::vector<std::string>& out)
{
    if (i >= delimiters.size())
    {
        out.push_back(str);
        return;
    }

    char d = delimiters[i][0];
    vector<string> v = Split(str, d);

    for (int j = 0; j < v.size(); ++j)
    {
        Split(v[j], delimiters, i + 1, out);
        if(j < v.size() - 1)
            out.push_back(string(1, d));
    }

}

void ReverseStack(stack<string>& st)
{
    stack<string> temp;
    while (!st.empty())
    {
        string top = st.top();
        temp.push(top);
        st.pop();
    }
    st = temp;
}

long long Calc(const vector<string>& exp, const vector<string>& op_seq)
{
    vector<string> v(begin(exp), end(exp));

    for (auto op : op_seq)
    {
        stack<string> st;

        for (int i = 0; i < v.size(); ++i)
        {
            if (v[i] == op)
            {
                i++;
                ll a = stoll(st.top());
                st.pop();
                ll b = stoll(v[i]);
                ll c;
                if (op == "+")
                    c = a + b;
                else if (op == "-")
                    c = a - b;
                else
                    c = a * b;
                st.push(to_string(c));
            }
            else
            {
                st.push(v[i]);
            }
        }

        ReverseStack(st);
        v.clear();

        while (!st.empty())
        {
            v.push_back(st.top());
            st.pop();
        }
    }

    return stoll(v[0]);
}

long long solution(string expression) 
{
    vector<string> ops = { "-", "+", "*" };
    sort(begin(ops), end(ops));

    ll max_val = 0;

    do
    {
        vector<string> exp;
        Split(expression, ops, 0, exp);

        ll val = abs(Calc(exp, ops));
        max_val = max(max_val, val);

    } while (next_permutation(begin(ops), end(ops)));

    return max_val;
}


int main()
{
    string expression = "100-200*300-500+20";

    auto answer = solution(expression);
    cout << answer << endl;

    return 0;
}

