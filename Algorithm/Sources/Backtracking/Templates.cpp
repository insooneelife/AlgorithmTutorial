


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
