#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
//#include "Print.h"

using namespace std;


static int BFS(const std::vector<std::vector<int>>& graph, int start, int finish)
{
    using namespace std;
    using Node = pair<int, int>;

    const int N = graph.size();
    vector<bool> visited(N, false);
    queue<Node> que;
    int ret = -1;

    que.push({ start, 0 });
    visited[start] = true;

    while (!que.empty())
    {
        Node state = que.front();
        int node = state.first;
        int cnt = state.second;

        if (node == finish)
        {
            ret = cnt;
            break;
        }

        for (int next = 0; next < N; ++next)
        {
            if (graph[node][next] == 1 && !visited[next])
            {
                que.push({ next, cnt + 1 });
                visited[next] = true;
            }
        }

        que.pop();
    }

    return ret;
}

int MatchCount(const string& a, const string& b)
{
    if (a.size() != b.size())
        return 0;

    int cnt = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] == b[i])
            cnt++;
    }
    return cnt;
}

int solution(string start, string target, vector<string> words)
{
    words.push_back(start);

    sort(begin(words), end(words));
    words.erase(unique(begin(words), end(words)), end(words));

    int start_idx = find(begin(words), end(words), start) - begin(words);
    int target_idx = find(begin(words), end(words), target) - begin(words);
    const int N = words.size();
    vector<vector<int>> graph(N, vector<int>(N, 0));

    // make graph
    for (int from = 0; from < N; ++from)
    {
        for(int to = 0; to < N; ++to)
        {
            int match_count = MatchCount(words[from], words[to]);
            int diff_count = words[from].size() - match_count;

            if (from == to || diff_count == 1)
            {
                graph[from][to] = 1;
                graph[to][from] = 1;
            }
        }
    }

    int ret = BFS(graph, start_idx, target_idx);
    return ret < 0 ? 0 : ret;
}

int main()
{
    string begin = "hit";
    string target = "cog";
    //vector<string> words = { "hot", "dot", "dog", "lot", "log", "cog" };
    vector<string> words = { "hot", "dot", "dog", "lot", "log" };
    

    int answer = solution(begin, target, words);
    cout << answer;

    return 0;
}