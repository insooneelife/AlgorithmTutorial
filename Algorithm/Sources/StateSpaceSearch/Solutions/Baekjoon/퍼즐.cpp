
// 퍼즐 (BFS)
// https://www.acmicpc.net/problem/1525

#include <vector>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct Node
{
    vector<int> state;
    int cnt;
};

struct Idx
{
    int i, j;
};

int ToKey(const vector<int>& state)
{
    int sum = 0;
    int mul = 1;
    for (int i = 0; i < state.size(); ++i)
    {
        sum += state[i] * mul;
        mul *= 10;
    }
    return sum;
}

bool Modify(const vector<int>& state, Idx dir, vector<int>& out)
{
    int puzzle[3][3];
    Idx zero = { 0, 0 };

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            puzzle[i][j] = state[i * 3 + j];
            if (puzzle[i][j] == 0)
            {
                zero.i = i;
                zero.j = j;
            }
        }
    }
    Idx pos = { zero.i + dir.i, zero.j + dir.j };
    
    if (0 <= pos.i && pos.i < 3 && 
        0 <= pos.j && pos.j < 3)
    {
        int zero_idx = zero.i * 3 + zero.j;
        int pos_idx = pos.i * 3 + pos.j;

        out = state;
        swap(out[zero_idx], out[pos_idx]);

        return true;
    }

    return false;
}

static int BFS(vector<int> start, vector<int> finish)
{
    const vector<Idx> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    queue<Node> que;
    set<int> visited;
    int ret = -1;

    que.push({ start, 0 });
    visited.insert(ToKey(start));

    while (!que.empty())
    {
        Node node = que.front();
        vector<int> state = node.state;
        int cnt = node.cnt;

        if (state == finish)
        {
            ret = cnt;
            break;
        }

        for (int i = 0; i < directions.size(); ++i)
        {
            Idx dir = directions[i];
            vector<int> next;
            if (Modify(state, dir, next))
            {
                int key = ToKey(next);
                if (visited.find(key) == end(visited))
                {
                    que.push({ next, cnt + 1 });
                    visited.insert(key);
                }
            }            
        }

        que.pop();
    }

    return ret;
}



int main()
{
    vector<int> start(9, 0);
    vector<int> finish = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

    for (int i = 0; i < 9; ++i)
        cin >> start[i];

    cout << BFS(start, finish);
    return 0;
}


