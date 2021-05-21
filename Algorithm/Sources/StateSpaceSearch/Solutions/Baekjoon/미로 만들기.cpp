
// 미로 만들기 (Lowest Cost First Search)
// https://www.acmicpc.net/problem/2665

#include <iostream>
#include <queue>
using namespace std;

int A[53][53] = {};
bool visit[53][53] = {};

struct State
{
    int i;
    int j;
};

struct Node 
{
public:
    Node(State state, int cnt) : state(state), cnt(cnt) {}

    bool operator<(Node other) const
    {
        return cnt > other.cnt;
    }

public:
    State state;
    int cnt;
};

void Input(int& n)
{
    char str[52];
    cin >> n;
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            A[i][j] = -1;
        }
    }
        
    for (int i = 1; i <= n; i++)
    {
        cin >> str;
        for (int j = 0; str[j]; j++)
        {
            A[i][j + 1] = str[j] - '0';
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i][j] == 1)A[i][j] = 0;
            else A[i][j] = 1;
        }
    }
}

int main() 
{   
    // input & make boundary
    int n;
    Input(n);

    const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    priority_queue<Node> pque;
    int all = 0;
    State start = { 1, 1 };
    Node node(start, A[start.i][start.j]);

    visit[start.i][start.j] = true;
    pque.push(node);

    while (!pque.empty())
    {
        node = pque.top();
        State state = node.state;
        int cnt = node.cnt;
        int i = state.i;
        int j = state.j;

        if (i == n && j == n)
            all = cnt;

        for (auto d : directions)
        {
            int nexti = i + d.first;
            int nextj = j + d.second;
            int val = A[nexti][nextj];

            if (val != -1 && !visit[nexti][nextj])
            {
                pque.push({ {nexti, nextj}, cnt + val });
                visit[nexti][nextj] = true;
            }
        }
        pque.pop();
    }
    cout << all;

    return 0;
}