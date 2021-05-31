
// 숫자 게임 (정렬)
// https://programmers.co.kr/learn/courses/30/lessons/12987

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<int> A, vector<int> B)
{
    vector<int> a, b;
    a.reserve(A.size());
    b.reserve(B.size());

    for (int i = 0; i < A.size(); ++i)
    {
        a.push_back(A[i]);
        b.push_back(B[i]);
    }

    sort(begin(a), end(a), greater<>());
    sort(begin(b), end(b), greater<>());

    int from = 0;
    int to = b.size() - 1;
    int cnt = 0;
    for (int i = from; from <= to; ++i)
    {
        if (a[i] < b[from])
        {
            from++;
            cnt++;
        }
        else
        {
            to--;
        }
    }

    return cnt;
}

int main()
{
    vector<int> A = { 5, 1, 3, 7 };
    vector<int> B = { 2, 2, 6, 8 };   

    cout << solution(A, B) << endl;

    return 0;
}