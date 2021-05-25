// 가장 큰 정사각형 찾기 (DP)
// https://programmers.co.kr/learn/courses/30/lessons/12905


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

