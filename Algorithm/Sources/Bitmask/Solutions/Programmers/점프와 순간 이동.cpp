// 점프와 순간 이동 
// https://programmers.co.kr/learn/courses/30/lessons/12980

// 시행착오
// 1. BFS 도전 (시간초과)

#include <bitset>
#include <iostream>
using namespace std;

int solution(int n)
{
    bitset<64> b(n);
    return b.count();
}

int main()
{
    int n = 5000;
    cout << solution(n);

    return 0;
}

/*
static int BFS(int finish)
{
    using namespace std;
    using Node = pair<int, int>;

    set<int> visited;

    queue<Node> que;
    int ret = -1;
    const int start = 0;

    que.push({ start, 0 });
    visited.insert(start);

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

        vector<int> nexts = { node * 2, node + 1 };
        vector<int> counts = { cnt, cnt + 1 };

        for (int i = 0; i < nexts.size(); ++i)
        {
            int next = nexts[i];
            int nextcnt = counts[i];

            if (visited.find(next) == end(visited))
            {
                que.push({ next, nextcnt });
                visited.insert(next);
            }
        }

        que.pop();
    }

    return ret;
}

int solution(int n)
{
    return BFS(n);
}
*/