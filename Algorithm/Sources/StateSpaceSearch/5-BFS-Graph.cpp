// BFS (Breadth First Search)

#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<vector<int>> graph =
{
    { 0, 1, 1, 0, 0, 0, 0 },
    { 1, 0, 0, 1, 1, 0, 0 },
    { 1, 0, 0, 0, 0, 1, 1 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0 }
};

void BFS(int start)
{
    const int N = graph.size();
    vector<bool> visited(N, false);
    queue<int> que;

    que.push(start);
    visited[start] = true;

    while (!que.empty())
    {
        int node = que.front();
        cout << node << " ";

        for (int i = 0; i < N; ++i)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                que.push(i);
                visited[i] = true;
            }
        }
        que.pop();
    }
}

int main()
{
    BFS(0);
    return 0;
}

