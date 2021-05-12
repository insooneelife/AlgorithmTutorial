
// [1차] 프렌즈4블록
// https://programmers.co.kr/learn/courses/30/lessons/17679

// 시행착오
// 1. 삭제된 개수를 카운팅하는 부분이 조금 성가심

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
//#include "Utility.h"
//#include "Print.h"

using namespace std;

const vector<pair<int, int>> positions = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };

void Print(const vector<string>& board)
{
    for (auto b : board)
    {
        cout << b << endl;
    }
}

bool Check4x4(const vector<string>& board, int si, int sj)
{
    char target = board[si][sj];

    for (auto p : positions)
    {
        int ri = si + p.first;
        int rj = sj + p.second;

        if (target != board[ri][rj])
        {
            return false;
        }
    }
    return true;
}

int Remove4x4(vector<string>& board, int si, int sj)
{
    int cnt = 0;
    for (auto p : positions)
    {
        int ri = si + p.first;
        int rj = sj + p.second;

        if (board[ri][rj] != ' ')
        {
            board[ri][rj] = ' ';
            cnt++;
        }
    }
    return cnt;
}

int RemoveAll4x4(vector<string>& board, int m, int n)
{
    vector<pair<int, int>> removes;
    for (int i = 0; i < m - 1; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
        {
            if (board[i][j] == ' ')
                continue;

            if (Check4x4(board, i, j))
            {
                removes.push_back(make_pair(i, j));
            }
        }
    }

    int removed = 0;
    for (auto e : removes)
    {
        removed += Remove4x4(board, e.first, e.second);
    }

    return removed;
}

void SlidDown(vector<string>& board, int m, int n)
{
    for (int i = m - 1; i >= 1; --i)
    {
        for (int j = 0; j < n; ++j)
        {
            if(board[i][j] == ' ')
                swap(board[i][j], board[i - 1][j]);
        }
    }
}

void SlideAllDown(vector<string>& board, int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        SlidDown(board, m, n);
    }
}

int solution(int m, int n, vector<string> board) 
{
    int answer = 0;
    int removed = numeric_limits<int>::max();
    
    while (removed > 0)
    {
        removed = RemoveAll4x4(board, m, n);
        answer += removed;
        SlideAllDown(board, m, n);
    }    

    return answer;
}

int main()
{
    /*
    int m = 4;
    int n = 5;
    vector<string> board = 
    { 
        "CCBDE",
        "AAADE", 
        "AAABF",
        "CCBBF" 
    };
    */

    int m = 6;
    int n = 6;
    vector<string> board =
    {
        "TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ"
    };



    cout << solution(m, n, board);

    return 0;
}