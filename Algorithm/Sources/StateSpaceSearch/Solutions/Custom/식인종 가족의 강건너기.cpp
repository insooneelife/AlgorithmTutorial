/*
문제.

두 개의 섬이 있고 한쪽 섬에는 조련사, 사자, 아빠, 딸, 엄마, 아들과 배가 있다.
이 사람들은 반대편 섬으로 이동해야 하는데 문제가 있다.
만약 조련사가 없을 경우 사자는 모두을 잡아먹는다.
아빠가 없을 경우 엄마가 아들을 죽인다.
엄마가 없을 경우 아빠가 딸을 죽인다.
하지만 배를 움직일 수 있는 사람은 엄마, 아빠, 조련사 이 셋뿐이다.
그리고 보트에는 2명만 탑승할 수 있다.
아무도 죽지 않으며 반대편 섬으로 가려면 어떻게 이동시켜야 할까?

[섬A]                      [섬B]
조련사  ㅣ              ㅣ    
사자    ㅣ              ㅣ
아빠    ㅣ      강      ㅣ  
딸      ㅣ(배)          ㅣ
엄마    ㅣ              ㅣ
아들    ㅣ              ㅣ

*/


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <stack>
#include <bitset>
#include <unordered_map>

using namespace std;
typedef bitset<7> State;

struct Node
{
    State state;
    int cnt;
};

enum
{
    Mom, Dad, Son, Daughter, Trainer, Lion, Boat, Max
};


void PrintData(const State& data, const State& prev_data)
{
    const vector<string> entity_string = { "Mom", "Dad", "Son", "Daughter", "Trainer", "Lion", "Boat" };

    // diff to get move data
    State move(data ^ prev_data);
    string leftState = "";
    string rightState = "";
    string moved = "";

    bool moveRight = data[Boat];

    for (int i = 0; i < Boat; ++i)
    {
        if (data[i])
        {
            rightState += " (" + entity_string[i] + ") ";
        }
        else
        {
            leftState += " (" + entity_string[i] + ") ";
        }
        if (move[i])
            moved += " (" + entity_string[i] + ") ";
    }

    if (moved != "")
    {
        moved = (data[Boat] ? "[ToRight]  " : "[ToLeft]  ") + moved;
    }

    cout << "  |    " << leftState << "~~~~~~~~~~~~~~~~~~~~~~" << rightState << "  |    " << moved << endl << endl;
}


bool CheckAlive(const State& state)
{
    if (!state[Dad] && state[Mom] && state[Son])
    {
        return false;
    }

    if (!state[Mom] && state[Dad] && state[Daughter])
    {
        return false;
    }

    if ((!state[Trainer] && state[Lion]) &&
        (state[Dad] || state[Mom] || state[Son] || state[Daughter]))
    {
        return false;
    }
    return true;
}

bool CheckBothAlive(const State& state)
{
    State opposite(~state);

    if (!CheckAlive(opposite))
    {
        return false;
    }

    if (!CheckAlive(state))
    {
        return false;
    }
    return true;
}

bool CanControlBoat(State move)
{
    if (move[Mom] || move[Dad] || move[Trainer])
        return true;
    return false;
}

void Push(queue<Node>& que, vector<bool>& visited, vector<int>& backtrack, const Node& next, int current_key)
{
    int next_key = next.state.to_ulong();
    que.push(next);
    visited[next_key] = true;
    backtrack[next_key] = current_key;
}

void BFS(State start, State finish, vector<int>& backtrack)
{
    queue<Node> que;
    vector<bool> visited(1 << Max);

    Push(que, visited, backtrack, { start, 0 }, 0);

    while (!que.empty())
    {
        Node node = que.front();
        State state = node.state;
        unsigned long key = state.to_ulong();

        if (state == finish)
        {
            cout << "min cost : " << node.cnt << endl;
            break;
        }

        vector<State> moves;
        // one entity move
        for (int i = 0; i < Boat; ++i)
        {
            if (state[i] != state[Boat])
                continue;

            moves.push_back(State(1 << i));
        }

        // two entities move
        for (int i = 0; i < Boat; ++i)
        {
            for (int j = i + 1; j < Boat; ++j)
            {
                if (state[i] != state[Boat] || state[j] != state[Boat])
                    continue;

                moves.push_back(State((1 << i) | (1 << j)));
            }
        }

        for (State move : moves)
        {
            // toggle move, entities means they are moved to other side 
            State next(state ^ (move | State(1 << Boat)));
            unsigned long next_key = next.to_ulong();

            if (CheckBothAlive(next) && !visited[next_key] && CanControlBoat(move))
            {
                Push(que, visited, backtrack, { next, node.cnt + 1 }, key);
            }
        }
        que.pop();
    }
}

// make path from backtrack data
void MakePath(const vector<int>& backtrack, State start, State finish)
{
    std::stack<unsigned long> stack;
    unsigned long stateId = finish.to_ulong();
    stack.push(stateId);

    while (stateId != start.to_ulong())
    {
        stateId = backtrack[stateId];
        stack.push(stateId);
    }

    State prev = stack.top();
    while (!stack.empty())
    {
        State data = stack.top();

        PrintData(data, prev);

        prev = data;
        stack.pop();
    }
}

int main()
{
    // set all left(false)
    State start;
    start.reset();

    // set all right(true)
    State finish;
    finish.set();

    vector<int> backtrack(128);
    BFS(start, finish, backtrack);
    MakePath(backtrack, start, finish);


    return 0;
}