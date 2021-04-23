// ¹Ì·Î Å½»ö
// https://www.acmicpc.net/problem/2178

#include <iostream>
#include <queue>
using namespace std;

const int N = 100;
int arr[N][N] = {};

struct State
{
    int i, j;
    int cnt;
    State() : i(0), j(0), cnt(0) {}
    State(int i, int j, int cnt) : i(i), j(j), cnt(cnt) {}
};

bool IsValid(int n, int m, int i, int j)
{
    return 0 <= i && i < n && 0 <= j && j < m;
}

bool Check(int n, int m, int i, int j)
{
    return IsValid(n, m, i, j) && arr[i][j] == 1;
}

void MakeDirections(int dir, int i, int j, int& out_i, int& out_j)
{
    const static vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    out_i = i + directions[dir].first;
    out_j = j + directions[dir].second;
}

int BFS(int n, int m)
{
    queue<State> que;
    bool visited[N][N] = {};

    int from_i = 0;
    int from_j = 0;
    int to_i = n - 1;
    int to_j = m - 1;

    que.push(State(0, 0, 1));
    visited[0][0] = true;


    while (!que.empty())
    {
        State s = que.front();
        int i = s.i;
        int j = s.j;
        int cnt = s.cnt;

        // actions
        for (int dir = 0; dir < 4; ++dir)
        {
            int next_i;
            int next_j;
            MakeDirections(dir, i, j, next_i, next_j);

            if (Check(n, m, next_i, next_j) && !visited[next_i][next_j])
            {
                que.push(State(next_i, next_j, cnt + 1));
                visited[next_i][next_j] = true;
            }
        }

        if (i == to_i && j == to_j)
        {
            return cnt;
        }

        que.pop();
    }

    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    // input
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            char a;
            cin >> a;

            arr[i][j] = a - '0';
        }
    }

    int cnt = BFS(n, m);

    cout << cnt;

    return 0;
}