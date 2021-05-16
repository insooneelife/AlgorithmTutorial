
// 게임 맵 최단거리
// https://programmers.co.kr/learn/courses/30/lessons/1844

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct Vec
{
    int i, j;
};

struct State
{
    int i, j, cnt;
};

static bool InArray2D(int rows, int columns, int i, int j)
{
    return
        0 <= i && i < rows &&
        0 <= j && j < columns;
}

static int BFS(const std::vector<std::vector<int>>& maps, Vec from, Vec to)
{
    using namespace std;

    const int rows = maps.size();
    const int columns = maps[0].size();
    const vector<Vec> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    vector<vector<bool>> visited(rows, vector<bool>(columns, false));
    queue<State> que;

    int ret = -1;

    que.push({ from.i, from.j, 1 });
    visited[from.i][from.j] = true;

    while (!que.empty())
    {
        State state = que.front();

        if (state.i == to.i && state.j == to.j)
        {
            ret = state.cnt;
            break;
        }

        for (auto d : directions)
        {
            int nexti = state.i + d.i;
            int nextj = state.j + d.j;

            if (InArray2D(rows, columns, nexti, nextj) &&
                maps[nexti][nextj] == 1 &&
                !visited[nexti][nextj])
            {
                que.push({ nexti, nextj, state.cnt + 1 });
                visited[nexti][nextj] = true;
            }
        }
        que.pop();
    }

    return ret;
}

int solution(vector<vector<int> > maps)
{
    const int rows = maps.size();
    const int columns = maps[0].size();

    return BFS(maps, { 0, 0 }, { rows - 1, columns - 1 });
}

int main()
{
    vector<vector<int> > maps =
    {
        {1,0,1,1,1},
        {1,0,1,0,1},
        {1,0,1,1,1},
        {1,1,1,0,1},
        {0,0,0,0,1}
    };

    int answer = solution(maps);
    cout << answer;

    return 0;
}