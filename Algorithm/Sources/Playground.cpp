// 백트래킹


// N-Queen
// https://www.acmicpc.net/problem/9663


#include <iostream>
#include <vector>
using namespace std;

const vector<int> papers = { 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1 };
const int N = 10;
int board[N][N] = {};

void PrintBoard(int n, string tag)
{
    cout << tag << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool InBoard(int n, int si, int sj)
{
    return
        0 <= si && si < n &&
        0 <= sj && sj < n;
}

void SetBoard(int n, int si, int sj, int flag)
{
    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };

    board[si][sj] += flag;
    for (auto dir : directions)
    {
        int mi = dir.first;
        int mj = dir.second;

        int next_i = si + mi;
        int next_j = sj + mj;

        while (InBoard(n, next_i, next_j))
        {
            board[next_i][next_j] += flag;

            next_i = next_i + mi;
            next_j = next_j + mj;
        }
    }
}

void Paper(int k)
{
    using namespace std;

    if (k == 0)
    {
        return;
    }

    //int start = combs.size() > 0 ? combs.back() + 1 : 0;
    for (int i = 0; i < papers.size(); ++i)
    {
        // set board

        Paper(k - 1);

        // recover board
    }
}

int main()
{
    int n;
    cin >> n;




    return 0;
}













