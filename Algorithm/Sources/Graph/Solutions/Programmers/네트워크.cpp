// 네트워크 (BFS or DFS)
// https://programmers.co.kr/learn/courses/30/lessons/43162

#include <string>
#include <vector>
#include <iostream>

using namespace std;

int DFS(const vector<vector<int>>& graph, vector<bool>& visited, int node)
{   
    if (visited[node])
        return 0;

    int cnt = 1;
    visited[node] = true;

    for (int i = 0; i < graph[node].size(); ++i)
    {
        if(graph[node][i] == 1 && !visited[i])
            cnt += DFS(graph, visited, i);
    }
    return cnt;
}

int solution(int n, vector<vector<int>> computers) 
{
    vector<bool> visited(n);
    int answer = 0;

    for (int i = 0; i < n; ++i)
    {
        int cnt = DFS(computers, visited, i);
        if (cnt > 0)
        {
            answer++;
        }
    }

    return answer;
}

int main()
{
    /*
    int n = 3;
    vector<vector<int>> computers =
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    */

    int n = 6;
    vector<vector<int>> computers =
    {
        {1, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 1}
    };

    int answer = solution(n, computers);
    cout << answer;

    return 0;
}