
// 지형 이동 (DFS, BFS, Heap, UnionFind)
// https://programmers.co.kr/learn/courses/30/lessons/62050

// 문제 해결
// 1. DFS를 이용하여 분리된 영역들 간 index map을 생성한다.
// ex)
// 0 0 0 0
// 1 2 2 0
// 1 2 2 0
// 1 1 1 1

// 2. 모든 영역들에 대해서, 영역과 영역의 경계선이 되는 부분들의 distance를 우선순위큐에 저장한다.
// 정렬은 distance 기준으로 하고, 영역 인덱스도 추가로 저장한다.

// 3. 우선순위큐에서 distance가 작은 순서대로 노드를 빼고, 노드의 저장된 두 영역 인덱스를 참조하여
// 상호배타적 집합(UnionFind)을 채운다.
// 집합에 원소를 추가하기 전에 두 영역이 이미 합쳐져 있는지 검사하고,
// 합쳐지지 않은 경우에만 영역을 합치고, 그 때의 distance 값을 누적시킨다.

// 4. 누적된 distance 값 = answer

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include "Print.h"
using namespace std;

struct Idx
{
    int i;
    int j;
};

struct Node
{
public:
    Node(Idx state, int distance) : state(state), distance(distance) {}

    bool operator<(Node other) const
    {
        return distance > other.distance;
    }

public:
    Idx state;
    int distance;
};

#include <iostream>
#include <vector>
using namespace std;

struct RankedUnionFind
{
    vector<int> parent;
    vector<int> rank;

    RankedUnionFind(int n) : parent(n), rank(n, 1)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int Find(int i)
    {
        if (i == parent[i]) return i;
        return parent[i] = Find(parent[i]);
    }

    void Union(int a, int b)
    {
        int root1 = Find(a);
        int root2 = Find(b);

        if (root1 == root2)
            return;

        if (rank[root1] > rank[root2]) swap(root1, root2);
        parent[root1] = root2;
        if (rank[root1] == rank[root2]) ++rank[root2];
    }
};


static bool InArray2D(int rows, int columns, int i, int j)
{
    return
        0 <= i && i < rows &&
        0 <= j && j < columns;
}

const vector<Idx> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

// for make index map
static int DFS(
    const std::vector<std::vector<int>>& board,
    std::vector<std::vector<bool>>& visited,
    vector<vector<int>>& indexmap,
    const int height,
    const int index,
    int i,
    int j)
{
    const int M = board.size();
    const int N = board[0].size();

    if (visited[i][j])
        return 0;

    int cnt = 1;
    visited[i][j] = true;
    indexmap[i][j] = index;

    for (auto p : directions)
    {
        int nexti = i + p.i;
        int nextj = j + p.j;

        if (!InArray2D(M, N, nexti, nextj))
            continue;

        int distance = abs(board[i][j] - board[nexti][nextj]);

        if (distance <= height && !visited[nexti][nextj])
            cnt += DFS(board, visited, indexmap, height, index, nexti, nextj);

    }
    return cnt;
}

static void BFS(
    const vector<vector<int>>& maps,
    const vector<vector<int>>& indexmap, 
    priority_queue<Node>& boundary,
    vector<vector<bool>>& visited,
    const int height, 
    Idx from)
{
    if (visited[from.i][from.j])
        return;

    const int rows = maps.size();
    const int columns = maps[0].size();
    queue<Node> que;

    int ret = -1;
    que.push({ {from.i, from.j}, 1 });
    visited[from.i][from.j] = true;

    while (!que.empty())
    {
        Node data = que.front();
        Idx state = data.state;
        int i = state.i;
        int j = state.j;

        for (auto d : directions)
        {
            int nexti = i + d.i;
            int nextj = j + d.j;

            if (!InArray2D(rows, columns, nexti, nextj))
                continue;

            int distance = abs(maps[i][j] - maps[nexti][nextj]);
            int fromindex = indexmap[i][j];
            int toindex = indexmap[nexti][nextj];

            if (fromindex != toindex)
            {
                boundary.push({ {fromindex, toindex}, distance });
            }

            if (distance <= height && !visited[nexti][nextj])
            {
                que.push({ {nexti, nextj}, data.distance + 1 });
                visited[nexti][nextj] = true;
            }
        }
        que.pop();
    }
}

int solution(vector<vector<int>> land, int height)
{
    const int M = land.size();
    const int N = land[0].size();

    vector<vector<bool>> visited(M, vector<bool>(N, false));
    vector<vector<int>> indexmap(M, vector<int>(N));
    int index = 0;

    // make indexmap
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            int cnt = DFS(land, visited, indexmap, height, index, i, j);
            if (cnt > 0)
            {
                index++;
            }
        }
    }
    //Print::ContainerInContainer(indexmap);

    // make boundary
    priority_queue<Node> boundary;
    fill(begin(visited), end(visited), vector<bool>(N, false));

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            BFS(land, indexmap, boundary, visited, height, { i, j });
        }
    }

    // index exclusive set by UnionFind
    int ans = 0;
    RankedUnionFind uf(index);

    while (!boundary.empty())
    {
        Node node = boundary.top();
        int a = uf.Find(node.state.i);
        int b = uf.Find(node.state.j);

        if (a != b)
        {
            //cout << node.distance << "   " << node.state.i << " " << node.state.j << endl;
            uf.Union(node.state.i, node.state.j);
            ans += node.distance;
        }
        boundary.pop();
    }

    return ans;
}

int main()
{
    //vector<vector<int>> land = { {1, 4, 8, 10} ,{5, 5, 5, 5},{10, 10, 10, 10},{10, 10, 10, 20} };
    //int height = 3;

    vector<vector<int>> land = { {10, 11, 10, 11} ,{2, 21, 20, 10},{1, 20, 21, 11},{2, 1, 2, 1} };
    int height = 1;

    

    cout << solution(land, height);

    return 0;
}