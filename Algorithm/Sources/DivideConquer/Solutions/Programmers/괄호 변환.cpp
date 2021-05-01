// 괄호 변환 (분할정복)
// https://programmers.co.kr/learn/courses/30/lessons/60058

// 시행착오
// string cut = u.substr(1, u.size() - 2); 에서  u.size를 str.size로 잘못 작성함

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <bitset>
#include <functional>
#include <sstream>

using namespace std;

const char Open = '(';
const char Close = ')';

void Divide(string str, bool open, string& u, string& v)
{
    stack<char> st;
    char check_top = open ? Open : Close;
    int i = 0;
    st.push(str[i++]);

    while (!st.empty())
    {
        char top = st.top();
        if (top == check_top)
        {
            if (str[i] == check_top)
            {
                st.push(top);
            }
            else
            {
                st.pop();
            }
        }
        i++;
    }

    u = str.substr(0, i);
    v = str.substr(i, str.size() - i);
    //cout << "u : " << u << "  v : " << v << endl << endl;
}

string solution(string str)
{
    string u, v;
    if (str == "")
        return "";

    if (str[0] == Open)
    {
        Divide(str, true, u, v);
        return u + solution(v);
    }
    else
    {
        Divide(str, false, u, v);
        string temp = Open + solution(v) + Close;
        string cut = u.substr(1, u.size() - 2);

        for (int j = 0; j < cut.size(); ++j)
        {
            if (cut[j] == Open)
            {
                cut[j] = Close;
            }
            else
            {
                cut[j] = Open;
            }
        }

        return temp + cut;
    }
}