
// TICTACTOE (DP)
// https://algospot.com/judge/problem/read/TICTACTOE

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char X = 'x';
const char O = 'o';
const char Blank = '.';

const int CantPlay = 2;
const int CanWin = 1;
const int CanTie = 0;
const int Lose = -1;

const int NotSet = -2;

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
            else
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
        return Lose;
    }

    int board_key = ToKey(board);
    if (mem[board_key] != NotSet)
        return mem[board_key];

    int minv = CantPlay;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == Blank)
            {
                board[i][j] = turn;
                minv = min(minv, TicTacToe(board, next_turn));
                board[i][j] = Blank;
            }            
        }
    }

    // 게임을 더 이상 진행할수 없는 경우 or 비기는 경우
    if (minv == CantPlay || minv == CanTie)
        return mem[board_key] = CanTie;

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
        for (int i = 0; i < 3; ++i)
        {
            cin >> board[i];
        }

        int ans = TicTacToe(board, X);
        if (ans == CanWin)
        {
            cout << X << endl;
        }
        else if (ans == Lose)
        {
            cout << O << endl;
        }
        else
        {
            cout << "TIE" << endl;
        }
    }    
    
    return 0;

    
}