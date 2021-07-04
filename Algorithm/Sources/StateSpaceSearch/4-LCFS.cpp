


#include "Headers.h"
#include "Data.h"
using namespace std;

// 2D 배열 Lowest Cost First Search
// time complexity     O(N ^ 2 * logN)
// input               2D 배열(N ^ 2), 탐색시작 위치, 탐색중단 위치
// output              우선순위 단위 탐색
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
