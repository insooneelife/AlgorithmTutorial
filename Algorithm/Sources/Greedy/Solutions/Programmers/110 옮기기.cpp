
// 110 옮기기 (탐욕법)
// https://programmers.co.kr/learn/courses/30/lessons/77886


// 문제풀이
// 1. 모든 110을 추출한다. (stack을 이용하여 제거 후 만들어지는 케이스까지 제거한다.)
// 2. 모든 110이 제거된 문자열에서는 0이 나오기 전까지는 1이 두번 이상 연속될 수가 없다. (연속되었다면 제거되었을 것이다.)
// ex) 1001010001000, 0100101111111111
// 3. 그러므로 뒷부분은 연속된 1이 있을 것인데, 이것들을 문자열의 가장 뒷부분에 배치한다.
// 4. 그 후 추출한 110을 배치한다.
// 5. 나머지를 배치한다.


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
//#include "Print.h"
using namespace std;



string Make(const string& s)
{
    stack<char> st;
    int cnt = 0;

    for (int i = 0; i < s.size(); ++i)
    {
        char c = s[i];

        if (st.size() >= 2)
        {
            char b = st.top();
            st.pop();

            char a = st.top();
            st.pop();

            if (a == '1' && b == '1' && c == '0')
            {
                cnt++;
            }
            else
            {
                st.push(a);
                st.push(b);
                st.push(c);
            }
        }
        else
        {
            st.push(c);
        }
    }

    if (!cnt)
    {
        return s;
    }
    
    string str = "";

    // 연속된 1 뒷부분에 배치 (stack이기 때문에 역순)
    while (!st.empty())
    {
        if (st.top() == '0')
            break;

        str += st.top();
        st.pop();
    }
    
    // 011 배치
    while (cnt--)
    {
        str += "011";
    }

    // 나머지 배치
    while (!st.empty())
    {
        str += st.top();
        st.pop();
    }

    reverse(begin(str), end(str));

    return str;
}

vector<string> solution(vector<string> s) 
{
    vector<string> answer(s.size());
    
    for (int i = 0; i < s.size(); ++i)
    {
        answer[i] = Make(s[i]);
    }
    
    return answer;
}


int main()
{
    vector<string> s = { "1110", "100111100", "0111111010" };
    vector<string> answer = solution(s);
    //Print::Container(answer);

    return 0;
}
