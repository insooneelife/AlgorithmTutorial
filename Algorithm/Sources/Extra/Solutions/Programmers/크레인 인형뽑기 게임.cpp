
// 크레인 인형뽑기 게임
// https://programmers.co.kr/learn/courses/30/lessons/64061

#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

const int Invalid = -1;

int GetTop(vector<vector<int>>& board, int j)
{
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i][j] != 0)
        {
            int ret = board[i][j];
            board[i][j] = 0;
            return ret;
        }
    }
    return Invalid;
}

int solution(vector<vector<int>> board, vector<int> moves) 
{
    stack<int> basket;
    int cnt = 0;

    for (auto m : moves)
    {
        int index = m - 1;
        int top = GetTop(board, index);

        if (top != Invalid)
        {
            if (basket.size() > 0)
            {
                if (basket.top() == top)
                {
                    basket.pop();
                    cnt += 2;
                    continue;
                }
            }
            basket.push(top);
        }
    }

    return cnt;
}


int main()
{
    // answer = 4
    vector<vector<int>> board = 
    { 
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 3},
        {0, 2, 5, 0, 1},
        {4, 2, 4, 4, 2},
        {3, 5, 1, 3, 1} 
    };

    vector<int> moves = {1, 5, 3, 5, 1, 2, 1, 4} ;
    
    cout << solution(board, moves);

    return 0;
}