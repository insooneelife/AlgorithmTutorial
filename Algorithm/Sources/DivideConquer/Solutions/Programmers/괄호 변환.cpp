// 괄호 변환
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

int Divide(string str, bool open)
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
    
    return i;
}

string solution(string str) 
{
    if (str == "")
        return "";

    if (str[0] == Open)
    {
        int i = Divide(str, true);
        string u = str.substr(0, i);
        string v = str.substr(i, str.size() - i);
        //cout << "Currect  u : " << u << "  v : " << v << endl << endl;

        return u + solution(v);
    }
    else
    {
        int i = Divide(str, false);
        string u = str.substr(0, i);
        string v = str.substr(i, str.size() - i);
        //cout << "Balanced  u : " << u << "  v : " << v << endl << endl;

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

int main()
{
    string p = ")(";
    //string p = "(()())()";
    //string p = "()))((()";

    string answer = solution(p);

    cout << answer ;

    return 0;
}