// 블록 게임
// https://programmers.co.kr/learn/courses/30/lessons/42894

// 문제풀이
// 1. 탑다운 Black 블록을 내린다 (두 번 수행)
// 2. 직사각형 검사 및 직사각형 제거
// 3. Black 블록 복구
// 4. 위 과정을 N번 반복한다.

// 시행착오
// 1. 기역자 모양이 세워져 있는 경우까지 해결하기 위해 2개 라인을 Black으로 채운 후 직사각형으로 테스트해볼 필요가 있다.
// 2. 직사각형 테스트 중, 직사각형 모양이 나오더라도 Black의 개수가 더 많은 케이스는 유효하지 않은 케이스이다.

#include <string>
#include <vector>
#include <iostream>
//#include "Print.h"

using namespace std;

const int Black = 999;

struct Pos
{
    Pos() :i(-1), j(-1) {}
    Pos(int i, int j) : i(i), j(j) {}
    int i, j;
};

bool SetTopDown(const vector<vector<int>>& board, int j, Pos& pos)
{
    int index = -1;
    for (int i = 0; i < board.size(); ++i)
    {
        if (board[i][j] == 0)
        {
            index = i;
        }
        else
        {
            break;
        }
    }

    if (index >= 0)
    {
        pos.i = index;
        pos.j = j;
        return true;
    }
    return false;
}

bool InArray2D(int n, int a, int b)
{
    return  0 <= a && a < n && 0 <= b && b < n;
}

bool CheckRect(const vector<vector<int>>& board, const vector<Pos>& rect, int i, int j)
{
    int N = board.size();
    int target = board[i][j];
    int count_black = 0;
    for (Pos pos : rect)
    {
        int ri = i + pos.i;
        int rj = j + pos.j;

        if (!InArray2D(N, ri, rj))
        {
            return false;
        }

        if (board[ri][rj] == 0)
        {
            return false;
        }

        if (board[ri][rj] == Black)
        {
            count_black++;
        }
        else
        {
            target = board[ri][rj];
        }
    }

    if (count_black > 2)
    {
        return false;
    }

    for (Pos pos : rect)
    {
        int ri = i + pos.i;
        int rj = j + pos.j;

        if (board[ri][rj] != target && board[ri][rj] != Black)
        {
            return false;
            break;
        }
    }

    return true;
}

void RemoveRect(vector<vector<int>>& board, const vector<Pos>& rect, int i, int j)
{
    for (Pos pos : rect)
    {
        int ri = i + pos.i;
        int rj = j + pos.j;

        board[ri][rj] = 0;
    }
}

int RemoveRects(vector<vector<int>>& board)
{
    const vector<vector<Pos>> rects =
    {
        {
            Pos(0, 0), Pos(0, 1), Pos(0, 2),
            Pos(1, 0), Pos(1, 1), Pos(1, 2)
        },
        {
            Pos(0, 0), Pos(0, 1),
            Pos(1, 0), Pos(1, 1),
            Pos(2, 0), Pos(2, 1),
        }
    };

    int N = board.size();
    int cnt = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int target = board[i][j];

            if (target == 0)
                continue;
                
            for (const vector<Pos>& rect : rects)
            {
                if (CheckRect(board, rect, i, j))
                {
                    RemoveRect(board, rect, i, j);

                    cnt++;
                }

            }
        }
    }

    // count
    return cnt;
}

int solution(vector<vector<int>> board) 
{
    int N = board.size();
    int answer = 0;

    for (int t = 0; t < N; ++t)
    {
        vector<Pos> positions;
        for (int go = 0; go < 2; ++go)
        {
            for (int j = 0; j < N; ++j)
            {
                Pos pos;
                if (SetTopDown(board, j, pos))
                {
                    board[pos.i][pos.j] = Black;
                    positions.push_back(pos);
                }
            }
        }        

        int cnt = RemoveRects(board);
        //Print::ContainerInContainer(board);

        answer += cnt;

        // recover blacks
        for (Pos pos : positions)
        {
            board[pos.i][pos.j] = 0;
        }

        //Print::ContainerInContainer(board);
    }
    
    return answer;
}

int main()
{
    vector<vector<int>> board = 
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
        {0, 0, 0, 0, 0, 4, 4, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 4, 0, 0, 0},
        {0, 0, 0, 2, 3, 0, 0, 0, 5, 5},
        {1, 2, 2, 2, 3, 3, 0, 0, 0, 5},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 5} 
    };

    int answer = solution(board);

    cout << answer;

    return 0;
}