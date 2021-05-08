
// 호텔 방 배정 (분할정복)
// https://programmers.co.kr/learn/courses/30/lessons/64063

// 시행착오
// 1. 너무 어렵게 접근함 

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

using namespace std;
using ll = long long;

ll Find(map<ll, ll>& room, ll request)
{
    // 방이 비어있으면 배정
    if (room.find(request) == room.end())
        return room[request] = request; 

    // 방이 비어있지 않으면, 
    // 요청된 방에 마지막 배정된 방을 찾고,
    // 그 다음 방을 재귀적으로 다시 요청함
    ll next_req = room[request] + 1;

    // 최종적으로 방을 찾은 경우, 마지막 배정된 방 갱신
    return room[request] = Find(room, next_req); 
}

vector<ll> solution(ll k, vector<ll> room_number) 
{
    // 요청된 방 번호, 마지막으로 배정된 방 번호
    map<ll, ll> room;
    vector<ll> answer;

    for (ll r : room_number)
    {
        answer.push_back(Find(room, r));
    }
    return answer;
}


int main()
{
    //ll k = 10;
    //vector<ll> room_number = { 1, 3, 4, 1, 3, 1 };
    ll k = 10;
    vector<ll> room_number = { 1, 1, 1, 1, 5, 11, 1, 1, 1, 1 };
    vector<ll> answer = solution(k, room_number);

    Print::Container(answer);

    return 0;
}


