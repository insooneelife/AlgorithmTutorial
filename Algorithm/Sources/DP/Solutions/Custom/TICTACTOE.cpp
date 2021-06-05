
// TICTACTOE (DP)
// https://algospot.com/judge/problem/read/TICTACTOE

// 점화식
// F(board, turn) : 현재 보드 상태에서 현재 플레이어가 최적의 수를 두었을 때의 승, 패, 무승부 여부

// 부분 문제
// 현재 상태에서 임의의 공백 위치에 현재 플레이어가 수를 놓고 난 후의 board에서 상대방의 승, 패, 무승부 여부
// for all 공백위치:
//     setboard
//     F(board, other)
//     recoverboard

// 현재 가능한 모든 수들에 대한 상대방의 최적해들 중에서 가장 최소값을 찾는다. (상대방이 지는 경우 < 비기는 경우 < 이기는 경우)
// 더 이상 게임을 진행할 수 없는 경우 or 비기는 경우  무승부를 반환
// 상대방이 지는 경우 현재 플레이어는 승리를 반환
// 상대방이 이기는 경우 현재 플레이어는 패배를 반환

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char X = 'x';
const char O = 'o';
const char Blank = '.';
const int NotSet = -2;

enum Outcome
{
    Lose = -1, CanTie, CanWin, CantPlay
};

bool CheckLine(char a, char b, char c, char turn)
{
    return a == turn && b == turn && c == turn;
}

bool GameFinished(const vector<string>& board, char turn)
{
    for (int i = 0; i < 3; ++i)
        if (CheckLine(board[i][0], board[i][1], board[i][2], turn))
            return true;

    for (int j = 0; j < 3; ++j)
        if (CheckLine(board[0][j], board[1][j], board[2][j], turn))
            return true;

    if (CheckLine(board[0][0], board[1][1], board[2][2], turn))
        return true;

    if (CheckLine(board[0][2], board[1][1], board[2][0], turn))
        return true;
    return false;
}


// 각 board에 대한 유일한 값을 생성한다.
// board의 상태는 O, X, None 이므로 3진수 형태의 수로 치환할 수 있다.
int ToKey(const vector<string>& board)
{
    int key = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            key *= 3;
            if (board[i][j] == O)
                key++;
            else if (board[i][j] == X)
                key += 2;
        }
    }
    return key;
}

// 3 ^ 9
const int Size = 19683;
int mem[Size];

// 나의 차례
int TicTacToe(vector<string>& board, char turn)
{
    // 상대방 차례
    char next_turn = X + O - turn;

    // 상대가 둬서 게임이 끝난 경우 나는 Lose
    if (GameFinished(board, next_turn))
    {
        return Outcome::Lose;
    }

    int board_key = ToKey(board);
    if (mem[board_key] != NotSet)
        return mem[board_key];

    int minv = Outcome::CantPlay;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            // 공백인 위치에 수를 놓아본다.
            // turn은 상대방에게 넘어간다.
            if (board[i][j] == Blank)
            {
                board[i][j] = turn;
                minv = min(minv, TicTacToe(board, next_turn));
                board[i][j] = Blank;
            }
        }
    }

    // 게임을 더 이상 진행할수 없는 경우 or 비기는 경우
    if (minv == Outcome::CantPlay ||
        minv == Outcome::CanTie)
        return mem[board_key] = Outcome::CanTie;

    // 최선이 상대의 승리이면 나는 Lose
    // 최선이 상대의 패배이면 나는 Win
    return mem[board_key] = -minv;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        for (int i = 0; i < Size; ++i)
            mem[i] = NotSet;

        vector<string> board(3);
        int cnt = 0;
        for (int i = 0; i < 3; ++i)
        {
            cin >> board[i];

            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] != Blank)
                    cnt++;
            }
        }

        char start = (cnt % 2 == 0) ? X : O;
        char other_turn = X + O - start;
        int ans = TicTacToe(board, start);

        if (ans == Outcome::CanWin)
            cout << start << endl;
        else if (ans == Outcome::Lose)
            cout << O << endl;
        else
            cout << "TIE" << endl;

    }
}



/*
3
...
...
...
xx.
oo.
...
xox
oo.
x.x
*/

