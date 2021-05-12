
// [1차] 다트 게임
// https://programmers.co.kr/learn/courses/30/lessons/17682

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <bitset>
#include <algorithm>
#include <stack>
#include <cmath>

using namespace std;


int solution(string dartResult)
{
    stack<int> st;
    string num = "";
    int number = 0;
    bool inserted = false;

    for (int i = 0; i < dartResult.size(); ++i)
    {
        char c = dartResult[i];
        if ('0' <= c && c <= '9')
        {
            num += c;
            if (!inserted)
                st.push(number);
            inserted = true;
        }
        else if (c == 'S' || c == 'D' || c == 'T')
        {
            inserted = false;
            number = stoi(num);

            num = "";
            if (c == 'D')
            {
                number = pow(number, 2);
            }
            else if (c == 'T')
            {
                number = pow(number, 3);
            }
        }
        else
        {
            inserted = false;
            if (c == '*')
            {
                number = number * 2;
                int prev_number = st.top() * 2;
                st.pop();
                st.push(prev_number);
            }
            else if (c == '#')
            {
                number = number * -1;
            }
        }
    }
    st.push(number);

    int answer = 0;
    while (!st.empty())
    {
        answer += st.top();
        st.pop();
    }

    return answer;
}