// 호텔 방 배정 (Union-Find)
// https://programmers.co.kr/learn/courses/30/lessons/64063

// 시행착오
// 1. 호텔 방 번호가 Union-Find의 key가 되기 때문에, Union-Find의 parent와 같은 정보들을 map으로 저장해야 한다.
// 2. 방 번호와 같은 값이 key로 사용되는 상황에 Union-Find의 초기화를 미리 수행해둘 수 없기 때문에, 동적으로 초기화가 가능한 기능이 필요하다.
// 3. 값 오버플로우  
//    int recommend = uf.GetRecommend(room);  ->  ll recommend = uf.GetRecommend(room);

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <bitset>
#include <functional>
#include <sstream>

#include "Print.h"

using namespace std;
using ll = long long;

struct UnionFind
{
    map<ll, ll> parent;
    map<ll, int> rank;
    map<ll, ll> last;
    
    void Init(ll i)
    {
        auto it = parent.find(i);
        if (it == end(parent))
        {
            parent[i] = i;
            rank[i] = 1;
            last[i] = i;
        }
        else if(it->second == 0)
        {
            parent[i] = i;
            rank[i] = 1;
            last[i] = i;
        }
    }

    ll Find(ll i)
    {
        if (i == parent[i]) return i;
        return parent[i] = Find(parent[i]);
    }

    void Union(ll a, ll b)
    {
        ll root1 = Find(a);
        ll root2 = Find(b);

        if (root1 == root2)
            return;

        ll last_room = max(last[root1], last[root2]);

        if (rank[root1] > rank[root2])
            swap(root1, root2);

        parent[root1] = root2;
        last[root1] = last_room;
        last[root2] = last_room;

        if (rank[root1] == rank[root2]) 
            ++rank[root2];
    }

    ll GetRecommend(ll i)
    {
        ll root = Find(i);
        return last[root] + 1;
    }
};

void Insert(const int N, UnionFind& uf, set<ll>& occupy, ll room)
{
    occupy.insert(room);

    ll left = room - 1;
    ll right = room + 1;

    uf.Init(room);
    uf.Init(left);
    uf.Init(right);

    // left
    if (occupy.find(left) != end(occupy))
    {
        uf.Union(room, left);
    }

    // right
    if (occupy.find(right) != end(occupy))
    {
        uf.Union(room, right);
    }
}

vector<ll> solution(ll k, vector<ll> room_number) 
{
    const int N = room_number.size();
    UnionFind uf;
    set<ll> occupy;
    vector<ll> answer;

    for (int i = 0; i < N; ++i)
    {
        ll room = room_number[i];
        if (occupy.find(room) == end(occupy))
        {
            Insert(N, uf, occupy, room);
            answer.push_back(room);
        }
        else
        {
            ll recommend = uf.GetRecommend(room);
            Insert(N, uf, occupy, recommend);
            answer.push_back(recommend);
        }
    }

    return answer;
}


int main()
{
    //ll k = 10;
    //vector<ll> room_number = { 1, 3, 4, 1, 3, 1 };
    ll k = 14;
    vector<ll> room_number = { 1, 1, 1, 1, 5, 11, 1, 1, 1, 1 };
    vector<ll> answer = solution(k, room_number);

    Print::Container(answer);

    return 0;
}


