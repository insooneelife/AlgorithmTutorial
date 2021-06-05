// 가장 큰 정사각형 찾기 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12905

// F(i, j) : i, j 위치까지의 최대 정사각형의 한 변의 길이
 
// i = 4, j = 4 인 경우,
// i - 1, j 위치에 3x3 정사각형
// □□□□□
// □□■■■
// □□■■■
// □□■■■
// □□□□◆

// i - 1, j - 1 위치에 2x2 정사각형
// □□□□□
// □□□□□
// □□■■□
// □□■■□
// □□□□◆

// i - 1, j 위치에 3x3 정사각형
// □□□□□
// □□□□□
// □■■■□
// □■■■□
// □■■■◆

// 세 위치에 위와 같은 정사각형들이 있다고 가정했을때 전체 배열은 다음과 같은 모습이다.
// 위 세 경우를 합친 상황
// □□□□□
// □□■■■
// □■■■■
// □■■■■
// □■■■◆

// 위쪽과 왼쪽에 3x3 정사각형이 있었지만, 왼쪽+위쪽에 2x2 정사각형 때문에 현재 위치의 상태가 1이어도 최대 정사각형은 3x3이다.
// 즉 왼쪽, 위쪽, 왼쪽+위쪽 세 위치에서의 최소 정사각형 한 변의 길이 + 1 으로 표현될 수 있다.

// 점화식
// board[i][j] == 1 일 때,
// F(i, j) = min(F(i - 1, j), F(i, j - 1), F(i - 1, j - 1)) + 1
// board[i][j] == 0 일 때,
// F(i, j) = 0


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include "Print.h"
using namespace std;

int solution(vector<vector<int>> board)
{
    const int M = board.size();
    const int N = board[0].size();
    int max_len = 0;

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i == 0 || j == 0)
            {
                max_len = max(max_len, board[i][j]);
                continue;
            }

            if (board[i][j] != 0)
            {
                board[i][j] = min(min(board[i - 1][j], board[i][j - 1]), board[i - 1][j - 1]) + 1;
                max_len = max(max_len, board[i][j]);
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }

    return max_len * max_len;
}


int main()
{
    /*
    vector<vector<int>> board = 
    {
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 0, 1, 0} 
    };

    vector<vector<int>> board =
    {
        {0, 0, 1, 1},
        {1, 1, 1, 1}
    };
    */

    vector<vector<int>> board =
    {
        {1}
    };


    int answer = solution(board);

    cout << answer << endl;

    return 0;
}

