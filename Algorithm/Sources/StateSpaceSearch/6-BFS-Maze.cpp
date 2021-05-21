// BFS (Breadth First Search)

// 다음과 같은 미로가 주어졌을 때, 
// 이 미로의 (0, 0) 위치에서 (N - 1, N - 1) 위치까지 도달하기 위한 최소 이동 횟수를 구해보자.


#include <iostream>
#include <queue>
using namespace std;

const int N = 6;
int arr[N][N] =
{
    1,0,1,1,1,1,
    1,0,1,0,1,0,
    1,0,1,0,1,1,
    1,1,1,0,1,1,
    0,0,1,0,0,1,
    0,0,1,1,0,1
};

struct State
{
    State() : i(0), j(0) {}
    State(int i, int j) : i(i), j(j) {}

public:
    bool operator==(const State& other) const
    {
        return i == other.i && j == other.j;
    }

public:
    int i;
    int j;
};

struct Node
{
    State state;
    int cnt;
};


static bool InArray2D(int rows, int columns, int i, int j)
{
    return
        0 <= i && i < rows &&
        0 <= j && j < columns;
}

static int BFS(State from, State to)
{
    const int kCanMove = 1;
    const vector<pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    queue<Node> que;

    int ret = -1;

    que.push({ from, 1 });
    visited[from.i][from.j] = true;

    while (!que.empty())
    {
        Node node = que.front();
        State state = node.state;

        if (state == to)
        {
            ret = node.cnt;
            break;
        }

        for (auto d : directions)
        {
            int nexti = state.i + d.first;
            int nextj = state.j + d.second;

            if (InArray2D(N, N, nexti, nextj) &&
                arr[nexti][nextj] == kCanMove &&
                !visited[nexti][nextj])
            {
                que.push({ {nexti, nextj}, node.cnt + 1 });
                visited[nexti][nextj] = true;
            }
        }
        que.pop();
    }

    return ret;
}

int main()
{
    int cnt = BFS({ 0, 0 }, { N - 1, N - 1 });
    cout << cnt << endl;

    return 0;
}

