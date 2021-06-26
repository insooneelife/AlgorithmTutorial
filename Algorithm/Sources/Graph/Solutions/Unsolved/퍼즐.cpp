

// 퍼즐
// https://www.acmicpc.net/problem/1525

// 일반적인 해결방법은 StateSpaceSearch/Solutions/Baekjoon/퍼즐.cpp 에 있다.
// 이 방법은 그래프 매핑을 통해 문제 해결을 시도하였지만, 메모리 초과로 실패한 방법이다.

// 시행착오
// 1. 메모리 초과
// vector<vector<int>> 는 생각보다 메모리를 많이 잡아먹는다.
// int [][] 가 오히려 메모리 측면에서 훨씬 효율적이다.

// 2. 해시테이블의 reserve
// unordered_map에도 vector와 같이 reserve 함수가 존재한다.

#include <vector>
#include <iostream>
#include <queue>
#include <chrono>
#include <algorithm>
#include <map>
//#include "Print.h"
using namespace std;
using Node = pair<int, int>;

const int N = 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9;

struct Idx
{
    int i, j;

    int ToIndex() const { return i * 3 + j; }
    void FromIndex(int index) 
    {
        i = index / 3; 
        j = index % 3;
    }

    Idx operator+(const Idx& other) const
    {
        return { i + other.i, j + other.j };
    }
};

int ToKey(const vector<int>& state)
{
    int sum = 0;
    int mul = 1;
    for (int i = 0; i < state.size(); ++i)
    {
        sum += state[i] * mul;
        mul *= 10;
    }
    return sum;
}

vector<int> ToState(int key)
{
    vector<int> state(9);
    int i = 0;
    while (key > 0)
    {
        int val = key % 10;
        key /= 10;

        state[i++] = val;
    }
    return state;
}

bool IsValid(Idx pos)
{
    return 
        0 <= pos.i && pos.i < 3 &&
        0 <= pos.j && pos.j < 3;
}


static int BFS(const std::vector<std::vector<int>>& graph, int start, int finish)
{
    vector<bool> visited(N, false);
    queue<Node> que;
    int ret = -1;
    que.push({ start, 0 });
    visited[start] = true;

    int max_size = 0;

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

        for (int i = 0; i < graph[node].size(); ++i)
        {
            int next = graph[node][i];
            if (!visited[next])
            {
                que.push({ next, cnt + 1 });
                visited[next] = true;
            }
        }

        que.pop();
    }
    return ret;
}

int main()
{
    vector<int> start(9, 0);
    vector<int> finish = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

    for (int i = 0; i < 9; ++i)
        cin >> start[i];

    const vector<Idx> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    vector<vector<int>> graph(N);
    map<int, int> to_vertex;
  
    for (int i = 0; i < N; ++i)
        graph[i].reserve(4);
    
    //auto from = std::chrono::system_clock::now();
    //auto from_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(from);

    vector<int> state = finish;
    sort(begin(state), end(state));

    int vertex = 0;
    do
    {
        to_vertex.emplace(ToKey(state), vertex);
        vertex++;

    } while (next_permutation(begin(state), end(state)));

    for (auto e : to_vertex)
    {
        int key = e.first;
        int vertex = e.second;
        vector<int> state = ToState(key);

        int zindex = find(begin(state), end(state), 0) - begin(state);
        Idx pos;
        pos.FromIndex(zindex);

        for (auto dir : directions)
        {
            Idx npos = pos + dir;
            int nindex = npos.ToIndex();

            if (IsValid(npos))
            {
                swap(state[zindex], state[nindex]);
                int next = to_vertex[ToKey(state)];
                graph[vertex].push_back(next);
                swap(state[zindex], state[nindex]);
            }
        }
    }

    cout << BFS(graph, to_vertex[ToKey(start)], to_vertex[ToKey(finish)]);

    //auto to = std::chrono::system_clock::now();
    //auto to_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(to);
    //long duration = (to_ms.time_since_epoch() - from_ms.time_since_epoch()).count();
    //cout << duration << endl;

    return 0;
}
