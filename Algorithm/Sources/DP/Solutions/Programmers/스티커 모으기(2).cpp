
// 스티커 모으기(2)
// https://programmers.co.kr/learn/courses/30/lessons/12971

// 도둑질 (DP)    =>   동일 문제
// https://programmers.co.kr/learn/courses/30/lessons/42897

// 시행착오
// 1. 재귀함수로 작성 시 시간초과
// 2. 배열로 작성 시에도 재귀와 동일한 만큼의 인자를 사용하여야 함
// 3. D[0][x] 행은 의미가 없음
// 4. 2중 for loop 의 j는 0부터 시작해야 함.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ll D[3][100001] = { 0 };

int solution(vector<int> sticker)
{
    const int N = sticker.size();

    D[0][0] = sticker[0];
    D[0][1] = max((ll)sticker[1], D[0][0]);
    for (int i = 1; i <= 2; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i > j)
                D[i][j] = 0;
            else
                D[i][j] = max(D[i][j - 2] + (ll)sticker[j], D[i][j - 1]);
        }
    }

    ll case0 = (ll)sticker[0] + D[2][N - 2];
    ll case1 = (ll)sticker[N - 1] + D[1][N - 3];
    ll case2 = D[1][N - 2];

    return max(case0, max(case1, case2));
}

int main()
{
    //vector<int> sticker = { 14, 6, 5, 11, 3, 9, 2, 10 };
    vector<int> sticker = { 1, 3, 2, 5, 4 };
    cout << solution(sticker) << endl;

    return 0;
}