// 단체사진 찍기
// https://programmers.co.kr/learn/courses/30/lessons/1835

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
//#include "Print.h"

using namespace std;

bool Check(const vector<int> char_to_idx, const vector<int>& indices, string data)
{
    int from = find(begin(indices), end(indices), char_to_idx[data[0]]) - begin(indices);
    int to = find(begin(indices), end(indices), char_to_idx[data[2]]) - begin(indices);
    char op = data[3];
    int val = (data[4] - '0');
    int dis = abs(from - to) - 1;

    if (op == '<')
    {
        return dis < val;
    }
    else if (op == '>')
    {
        return dis > val;
    }
    else
    {
        return dis == val;
    }
}

bool CheckAll(const vector<string>& data, const vector<int> char_to_idx, const vector<int>& indices)
{
    for (const string& d : data)
    {
        if (!Check(char_to_idx, indices, d))
        {
            return false;
        }
    }
    return true;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) 
{
    vector<char> characters = { 'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T' };
    vector<int> char_to_idx(128);
    vector<int> indices = { 0, 1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < characters.size(); ++i)
    {
        char_to_idx[characters[i]] = i;
    }

    int answer = 0;
    do
    {
        if (CheckAll(data, char_to_idx, indices))
        {
            answer++;
        }

    } while (next_permutation(begin(indices), end(indices)));

    return answer;
}



int main()
{

    int n = 2;
    vector<string> data = { "N~F=0", "R~T>2" };

    int answer = solution(n, data);


    cout << answer;

    return 0;
}