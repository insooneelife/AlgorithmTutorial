// 가장 큰 수 (정렬)
// https://programmers.co.kr/learn/courses/30/lessons/42746?language=cpp


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
void Print(const vector<T>& v, string tag = "----------------------------")
{
    cout << tag << endl;
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << endl;
}


string solution(vector<int> numbers)
{
    vector<string> numstr(numbers.size());

    for (int i = 0; i < numbers.size(); ++i)
    {
        numstr[i] = to_string(numbers[i]);
    }

    sort(begin(numstr), end(numstr), [](const string& a, const string& b)
        {
            return a + b > b + a;
        });

    //Print(numstr);

    // check case  arr = {0, 0}
    if (numstr[0] == "0") return "0";

    string answer = "";
    for (int i = 0; i < numstr.size(); ++i)
    {
        answer += numstr[i];
    }

    return answer;
}