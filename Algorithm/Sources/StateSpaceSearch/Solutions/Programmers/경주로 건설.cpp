
// 경주로 건설 (LCFS)
// https://programmers.co.kr/learn/courses/30/lessons/67259



// 시행착오
// 1. LCFS를 이용하는 경우, next로 보낼 때, visited를 체크하게 되면, 문제가 생길 수 있다.
// 코스트를 멀리 보내는 브랜치의 경우, 다른 최적의 코스트가 도달하기 전에 미리 해당 공간을 점유해버릴 수 있기 때문이다.

// 2. 이 문제의 경우, 4방향에서 한 위치에 도달할 수 있는데, 
// 어느 방향으로부터 왔는지에 따라 같은 위치에 도달하더라도 그 때의 priority queue의 값이 최적값이 아닐 수 있다.
// 그러므로 visited 상태 정보에 방향에 대한 정보도 추가해 준다.

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

struct Idx
{
    int i;
    int j;

    bool operator==(const Idx& other) const
    {
        return i == other.i && j == other.j;
    }

    bool operator!=(const Idx& other) const
    {
        return !(*this == other);
    }

    Idx operator+(const Idx& other) const
    {
        return { i + other.i, j + other.j };
    }

    Idx operator-(const Idx& other) const
    {
        return { i - other.i, j - other.j };
    }
};

struct Node
{
public:
    bool operator<(Node other) const
    {
        return costs > other.costs;
    }

public:
    Idx state;
    int last_dir;
    int costs;
};

static bool InArray2D(int rows, int columns, int i, int j)
{
    return
        0 <= i && i < rows &&
        0 <= j && j < columns;
}

int LCFS(const vector<vector<int>>& board, Idx start, Idx finish)
{
    const vector<Idx> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    const int Rows = board.size();
    const int Columns = board[0].size();
    priority_queue<Node> pque;
    bool visited[25][25][4] = { false };
    int ret = 0;

    const int Line = 100;
    const int Corner = 500;

    pque.push({ start, 0, 0 });
    pque.push({ start, 2, 0 });

    while (!pque.empty())
    {
        Node node = pque.top();
        Idx state = node.state;
        Idx dir = directions[node.last_dir];
        int costs = node.costs;
        Idx prev = state - dir;
        pque.pop();

        if (visited[state.i][state.j][node.last_dir])
        {
            continue;
        }
        
        visited[state.i][state.j][node.last_dir] = true;

        if (state == finish)
        {
            ret = costs;
            break;
        }

        for (int i = 0; i < directions.size(); ++i)
        {
            Idx d = directions[i];
            Idx next = state + d;

            if (!InArray2D(Rows, Columns, next.i, next.j))
                continue;

            int cost = Line;
            if (dir != d)
            {
                cost += Corner;
            }

            if (board[next.i][next.j] != 1)
            {
                pque.push({ next, i, costs + cost });
            }
        }
    }

    return ret;
}

int solution(vector<vector<int>> board)
{
    return LCFS(board, { 0, 0 }, { (int)(board.size() - 1), (int)(board[0].size() - 1) });
}

int main()
{
    /*
    vector<vector<int>> board =
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    

    vector<vector<int>> board =
    {
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0}
    };

    
    vector<vector<int>> board = 
    {
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 1, 0, 1},
        {1, 0, 0, 0} 
    };
    

    vector<vector<int>> board =
    {
        {0,0,0,0,0,0},
        {0,1,1,1,1,0},
        {0,0,1,0,0,0},
        {1,0,0,1,0,1},
        {0,1,0,0,0,1},
        {0,0,0,0,0,0}
    };
    */

    /*
    vector<vector<int>> board =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 0, 0}
    };
    */
    // answer : 3000


    vector<vector<int>> board =
    {
        {0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0}
    };
    // answer : 6200    

    cout << solution(board);

    return 0;
}