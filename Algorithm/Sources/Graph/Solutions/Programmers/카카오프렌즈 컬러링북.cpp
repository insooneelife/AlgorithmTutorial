
// 카카오프렌즈 컬러링북 (DFS)
// https://programmers.co.kr/learn/courses/30/lessons/1829

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
//#include "Print.h"

using namespace std;

static bool InArray2D(int rows, int columns, int i, int j)
{
    return
        0 <= i && i < rows &&
        0 <= j && j < columns;
}

int DFS(const vector<vector<int>>& board, vector<vector<bool>>& visited, int search, int i, int j)
{
    const int M = board.size();
    const int N = board[0].size();

    if (visited[i][j])
        return 0;

    const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    int cnt = 1;
    visited[i][j] = true;
    
    for (auto p : directions)
    {
        int nexti = i + p.first;
        int nextj = j + p.second;

        if (!InArray2D(M, N, nexti, nextj))
            continue;

        if (board[nexti][nextj] == search && !visited[nexti][nextj])
            cnt += DFS(board, visited, search, nexti, nextj);
        
    }
    return cnt;
}

vector<int> solution(int m, int n, vector<vector<int>> picture) 
{
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<int> counts;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int val = picture[i][j];
            if (val != 0)
            {
                int cnt = DFS(picture, visited, val, i, j);
                if(cnt != 0)
                    counts.push_back(cnt);
            }
        }
    }


    return { (int)counts.size(), *max_element(begin(counts), end(counts)) };
}

int main()
{
    int m = 6;
    int n = 4;
    vector<vector<int>> picture = 
    {
        {1, 1, 1, 0},
        {1, 2, 2, 0},
        {1, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 3},
        {0, 0, 0, 3} 
    };

    vector<int> answer = solution(6, 4, picture);

    //Print::Container(answer);

    return 0;
}