


#include "Headers.h"
#include "Data.h"
#include <vector>



// 2D 배열판 탐색 경로를 구한다.
// 단, 탐색중에 backtrack 정보를 생성하며 탐색해야한다.
// time complexity     O(D)
// input        backtrack 정보, 마지막 방문 위치
// output       탐색 경로
static std::vector<Idx> MakeSearchPath(const std::map<Idx, Idx>& backtrack, Idx last)
{
    using namespace std;
    vector<Idx> path;
    Idx node = last;
    while (!(node == backtrack.at(node)))
    {
        path.push_back(node);
        node = backtrack.at(node);
    }
    path.push_back(node);

    reverse(begin(path), end(path));

    return path;
}

// 2D 배열(게임판) 깊이우선탐색
// time complexity     O(N ^ 2)
// input               2D 배열(N ^ 2), 방문기록 배열(N ^ 2), 탐색 가능한 값, 탐색시작 위치
// available(1)은 갈 수 있는 길이고, 그 외는 갈 수 없는 값이다.
// { 1, 0, 1, 1, 1 },
// { 1, 0, 1, 0, 1 },
// { 1, 0, 1, 1, 1 },
// { 1, 1, 1, 0, 1 },
// { 0, 0, 0, 0, 1 }
// output              방문한 노드 수, 방문기록
static int DFS(
    const std::vector<std::vector<int>>& board,
    std::vector<std::vector<bool>>& visited,
    const int available,
    int i,
    int j)
{
    using namespace std;

    const int rows = board.size();
    const int columns = board[0].size();

    if (visited[i][j])
        return 0;

    const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    int cnt = 1;
    visited[i][j] = true;

    for (auto p : directions)
    {
        int nexti = i + p.first;
        int nextj = j + p.second;

        if (!Utility::InArray2D(rows, columns, nexti, nextj))
            continue;

        if (board[nexti][nextj] == available && !visited[nexti][nextj])
            cnt += DFS(board, visited, available, nexti, nextj);

    }
    return cnt;
}



// 2D 배열(게임판) 너비우선탐색
// time complexity     O(N ^ 2)
// input               2D 배열(N ^ 2), 탐색시작 위치, 탐색중단 위치
// 1은 갈 수 있는 길이고, 0은 갈 수 없는 길이다.
// { 1, 0, 1, 1, 1 },
// { 1, 0, 1, 0, 1 },
// { 1, 0, 1, 1, 1 },
// { 1, 1, 1, 0, 1 },
// { 0, 0, 0, 0, 1 }
// output              최단방문회수(길이 없는 경우 : -1)
static int BFS(const std::vector<std::vector<int>>& maps, Idx from, Idx to)
{
    using namespace std;
    const int CanMove = 1;
    const int rows = maps.size();
    const int columns = maps[0].size();
    const vector<Idx> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    vector<vector<bool>> visited(rows, vector<bool>(columns, false));
    queue<QueueData> que;

    int ret = -1;

    que.push({ from.i, from.j, 1 });
    visited[from.i][from.j] = true;

    while (!que.empty())
    {
        QueueData data = que.front();
        Idx state = data.state;

        if (state.i == to.i && state.j == to.j)
        {
            ret = data.cnt;
            break;
        }

        for (auto d : directions)
        {
            int nexti = state.i + d.i;
            int nextj = state.j + d.j;

            if (Utility::InArray2D(rows, columns, nexti, nextj) &&
                maps[nexti][nextj] == CanMove &&
                !visited[nexti][nextj])
            {
                que.push({ nexti, nextj, data.cnt + 1 });
                visited[nexti][nextj] = true;
            }
        }
        que.pop();
    }

    return ret;
}


// 2D 배열(게임판) 너비우선탐색 + 경로생성
static int BFS(const std::vector<std::vector<int>>& maps, Idx from, Idx to, std::vector<Idx>& path)
{
    using namespace std;
    const int CanMove = 1;
    const int rows = maps.size();
    const int columns = maps[0].size();
    const vector<Idx> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    vector<vector<bool>> visited(rows, vector<bool>(columns, false));
    queue<QueueData> que;
    map<Idx, Idx> backtrack;
    backtrack.insert(make_pair(from, from));

    int ret = -1;

    que.push({ from.i, from.j, 1 });
    visited[from.i][from.j] = true;

    while (!que.empty())
    {
        QueueData data = que.front();
        Idx state = data.state;

        if (state.i == to.i && state.j == to.j)
        {
            ret = data.cnt;
            path = MakeSearchPath(backtrack, to);
            break;
        }

        for (auto d : directions)
        {
            int nexti = state.i + d.i;
            int nextj = state.j + d.j;

            if (Utility::InArray2D(rows, columns, nexti, nextj) &&
                maps[nexti][nextj] == CanMove &&
                !visited[nexti][nextj])
            {
                que.push({ nexti, nextj, data.cnt + 1 });
                visited[nexti][nextj] = true;
                backtrack.insert(make_pair<Idx, Idx>({ nexti, nextj }, { state.i, state.j }));
            }
        }
        que.pop();
    }

    return ret;
}



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