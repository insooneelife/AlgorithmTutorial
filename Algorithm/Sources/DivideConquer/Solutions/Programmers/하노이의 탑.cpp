
// 하노이의 탑
// https://programmers.co.kr/learn/courses/30/lessons/12946

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
//#include "Print.h"
using namespace std;
const vector<int> U = { 1, 2, 3 };

void Hanoi(int n, int a, int b, vector<vector<int>>& answers)
{
    if (n == 1)
    {
        answers.push_back({ a, b });
        return;
    }

    vector<int> S = { a, b };
    vector<int> out;
    sort(begin(S), end(S));
    set_difference(begin(U), end(U), begin(S), end(S), back_inserter(out));
    int t = out[0];

    Hanoi(n - 1, a, t, answers);
    Hanoi(1, a, b, answers);
    Hanoi(n - 1, t, b, answers);
}

vector<vector<int>> solution(int n) 
{
    vector<vector<int>> answers;
    Hanoi(n, 1, 3, answers);
    return answers;
}

int main()
{
    int n = 2;
    vector<vector<int>> answer = solution(n);
    //Print::ContainerInContainer(answer);

    return 0;
}
