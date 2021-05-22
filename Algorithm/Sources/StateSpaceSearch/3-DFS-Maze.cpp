
// 다음과 같은 미로가 주어졌을 때, 
// 이 미로의 (0, 0) 위치에서 (N - 1, N - 1) 위치까지 도달 가능한지 확인하는 알고리즘을 작성해보자.


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

bool visited[N][N] = {};
const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
bool found = false;

bool IsValid(int n, int m, int i, int j)
{
    return 0 <= i && i < n && 0 <= j && j < m;
}

bool Check(int n, int m, int i, int j)
{
    return IsValid(n, m, i, j) && arr[i][j] == 1;
}

void DFS(int i, int j)
{
    visited[i][j] = true;
    if (i == N - 1 && j == N - 1)
        found = true;

    for (auto d : directions)
    {
        int nexti = i + d.first;
        int nextj = j + d.second;
        if(Check(N, N, nexti, nextj) && !visited[nexti][nextj])
            DFS(nexti, nextj);
    }
}

int main()
{
    DFS(0, 0);
    cout << found << endl;

    return 0;
}