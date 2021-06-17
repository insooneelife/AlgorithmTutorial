
// 여행경로 (그래프, 오일러 서킷)
// https://programmers.co.kr/learn/courses/30/lessons/43164


// 시행착오
// 1. 오일러 트레일을 구하는 문제에서도 그래프를 수정할 일은 없음 (그래프에 간선을 굳이 추가할 필요가 없음)
// 2. 오일러 트레일의 경우, u -> v 로의 간선이 여러개가 존재할 수 있다는 사실을 기억해야함 (이 부분은 인풋에서도 동일하게 적용됨)
// 3. 오일러 서킷일 수도 있음


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

// euler circuit
void EulerCircuit(
    vector<vector<int>>& graph,
    vector<int>& euler,
    int node)
{
    for (int i = 0; i < graph[node].size(); ++i)
    {
        while (graph[node][i] > 0)
        {
            graph[node][i]--;
            EulerCircuit(graph, euler, i);
        }
    }

    euler.push_back(node);
}

void EulerTrailOrCircuit(
    map<string, int>& idxmap,
    vector<vector<int>>& graph,
    vector<int>& euler,
    int start_node)
{
    if (start_node >= 0)
    {
        EulerCircuit(graph, euler, start_node);
    }
    else
    {
        int index = idxmap["ICN"];
        EulerCircuit(graph, euler, index);
    }

    reverse(begin(euler), end(euler));
}

vector<string> solution(vector<vector<string>> tickets)
{
    vector<string> airports;
    map<string, int> idxmap;

    for (const vector<string>& v : tickets)
    {
        string from = v[0];
        string to = v[1];
        airports.push_back(from);
        airports.push_back(to);
    }

    sort(begin(airports), end(airports));
    airports.erase(unique(begin(airports), end(airports)), end(airports));
    const int N = airports.size();

    // adjacency matrix graph
    vector<vector<int>> graph(N, vector<int>(N, 0));
    vector<int> odegrees(N, 0);
    vector<int> idegrees(N, 0);

    for (int i = 0; i < N; ++i)
    {
        idxmap[airports[i]] = i;
    }

    // make graph
    for (const vector<string>& v : tickets)
    {
        string from = v[0];
        string to = v[1];
        int fi = idxmap[from];
        int ti = idxmap[to];
        graph[fi][ti]++;

        odegrees[fi]++;
        idegrees[ti]++;
    }

    // find start, end node for euler trail
    int start_node = -1;
    for (int i = 0; i < odegrees.size(); ++i)
    {
        if (odegrees[i] == idegrees[i] + 1)
        {
            start_node = i;
        }
    }

    vector<string> answer;
    vector<int> euler;
    EulerTrailOrCircuit(idxmap, graph, euler, start_node);
    
    for (int e : euler)
    {
        answer.push_back(airports[e]);
    }

    return answer;
}



#include "Print.h"
int main()
{
    /*
    vector<vector<string>> tickets =
    {
        {"ICN", "JFK"},
        {"HND", "IAD"},
        {"JFK", "HND"} 
    };
    */
    
    
    /*
    vector<vector<string>> tickets = 
    {
        {"ICN", "SFO"},
        {"ICN", "ATL"},
        {"SFO", "ATL"},
        {"ATL", "ICN"},
        {"ATL", "SFO"}
    };
    */
    

    /*
    vector<vector<string>> tickets =
    {
        {"ICN", "B"},
        {"B", "ICN"},
        {"ICN", "A"},
        {"A", "D"},
        {"D", "A"}
    };
    // ans : ["ICN", "B", "ICN", "A", "D", "A"]
    */

    /*
    vector<vector<string>> tickets = 
    {
        {"ICN", "AAA"},
        {"ICN", "AAA"},
        {"ICN", "AAA"},
        {"AAA", "ICN"},
        {"AAA", "ICN"} 
    };
    // ans : ["ICN", "AAA", "ICN", "AAA", "ICN", "AAA"]
    */

    /*
    vector<vector<string>> tickets =
    {
        {"ICN", "COO"},
        {"ICN", "BOO"},
        {"COO", "ICN"},
        {"BOO", "DOO"}
    };
    // ans : ["ICN", "COO", "ICN", "BOO", "DOO"]
    */

    /*
    vector<vector<string>> tickets =
    {
        {"ICN", "SFO"},
        {"SFO", "ICN"},
        {"ICN", "SFO"},
        {"SFO", "QRE"}
    };
    // ans : ["ICN", "SFO", "ICN", "SFO", "QRE"]
    */

    /*
    vector<vector<string>> tickets =
    {
        {"ICN", "BOO"},
        {"ICN", "COO"},
        {"COO", "DOO"},
        {"DOO", "COO"},
        {"BOO", "DOO"},
        {"DOO", "BOO"},
        {"BOO", "ICN"},
        {"COO", "BOO"}
    };
    // ans : ["ICN", "BOO", "DOO", "BOO", "ICN", "COO", "DOO", "COO", "BOO"]
    */

    /*
    vector<vector<string>> tickets =
    {
        {"ICN", "A"},{"ICN", "B"},{"B", "ICN"}
    };
    // ans : ['ICN', 'B', 'ICN', 'A']
    */

    vector<vector<string>> tickets =
    {
        {"ICN", "A"},
        {"A", "C"},
        {"ICN", "B"},
        {"B", "ICN"}
    };
    // ans : ['ICN', 'B', 'ICN', 'A', 'C']


    vector<string> ans = solution(tickets);
    Print::Container(ans);


    return 0;
}