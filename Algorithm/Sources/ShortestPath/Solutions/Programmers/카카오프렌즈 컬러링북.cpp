
// 카카오프렌즈 컬러링북 (그래프, 플로이드)
// https://programmers.co.kr/learn/courses/30/lessons/1829

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
//#include "Algorithm.h"
//#include "Print.h"

using namespace std;


vector<vector<long long>> MakeInput(const int N, vector<vector<int>> inputs, bool bigraph = true)
{
    vector<vector<long long>> adj(N, vector<long long>(N, std::numeric_limits<int>::max()));

    for (int i = 0; i < inputs.size(); ++i)
    {
        int from = inputs[i][0] - 1;
        int to = inputs[i][1] - 1;
        int cost = inputs[i][2];

        adj[from][to] = min(adj[from][to], (long long)cost);
        if (bigraph)
        {
            adj[to][from] = min(adj[to][from], (long long)cost);
        }
    }
    return adj;
}

class Floyd
{
public:
    Floyd(const int N, vector<vector<int>> inputs) : N(N), adj(MakeInput(N, inputs))
    {
        Make();
    }

    int GetCost(int from, int to) const
    {
        return adj[from - 1][to - 1];
    }

private:
    void Make()
    {
        for (int i = 0; i < N; ++i)
            adj[i][i] = 0;

        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    }    

private:
    const int N;
    vector<vector<long long>> adj;
};

int solution(int N, vector<vector<int>> road, int K) 
{
    Floyd floyd(N, road);

    int answer = 0;
    for (int j = 1; j <= N; ++j)
    {
        int val = floyd.GetCost(1, j);
        if (val <= K)
        {
            answer++;
        }
    } 
     
    return answer;
}

int main()
{
    //int N = 5;
    //vector<vector<int>> road = { {1, 2, 1}, {2, 3, 3}, {5, 2, 2}, {1, 4, 2}, {5, 3, 1}, {5, 4, 2} };
    //int K = 3;

    int N = 6;
    vector<vector<int>> road = { {1, 2, 1},{1, 3, 2},{2, 3, 2},{3, 4, 3},{3, 5, 2},{3, 5, 3},{5, 6, 1} };
    int K = 4;
    auto answer = solution(N, road, K);

    cout << answer;
    
    return 0;
}
