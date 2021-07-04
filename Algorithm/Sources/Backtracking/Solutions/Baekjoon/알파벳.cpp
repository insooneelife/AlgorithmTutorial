// 알파벳 (백트래킹)
// https://www.acmicpc.net/problem/1987

#include <iostream>
using namespace std;

char arr[22][22] = { 0 };
bool visit[26];
int gap = 0;

void Move(int i, int j, int cnt) 
{
    if (arr[i][j] == 0)
        return;

    if (visit[arr[i][j] - 'A'])
        return;

    visit[arr[i][j] - 'A'] = true;

    Move(i + 1, j, cnt + 1);
    Move(i - 1, j, cnt + 1);
    Move(i, j + 1, cnt + 1);
    Move(i, j - 1, cnt + 1);

    if (gap < cnt)
        gap = cnt;

    visit[arr[i][j] - 'A'] = false;
}

int main() 
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++) 
    {
        for (int j = 0; j <= m + 1; j++) 
        {
            if (i == 0 || j == 0 || i == n + 1 || j == m + 1) 
            {
            }
            else 
            {
                cin >> arr[i][j];
            }
        }
    }

    Move(1, 1, 1);
    cout << gap;
    return 0;
}