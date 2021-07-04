


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
