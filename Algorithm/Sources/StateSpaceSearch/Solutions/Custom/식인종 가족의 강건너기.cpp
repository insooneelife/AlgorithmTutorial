/*
조련사  l              l    
사자    l              l
아빠    l      강      l   마을
딸      l   (보트)     l
엄마    l              l
아들    l              l
자 다음과 같은 곳이 있다.
이 사람들은 마을에 가야한다..
하지만 문제가 있다.
만약 조련사가 없을경우 사자는 모두을 잡아먹는다.
아빠가 없을경우 엄마가 아들을 죽이고
엄마가 없을경우 아빠가 딸을 죽인다.
하지만 보트를 움직일수 있는사람은 엄마,아빠,조련사 이 셋뿐이다.
어떻게 해야 아무도 죽지않고 마을로 갈수있을까???
그리고 보트에는 2명밖에 탈수가 없다
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

void Push(queue<State>& que, vector<bool>& visited, vector<int>& backtrack, const State& state, int saveStateId)
{
    int stateId = state.to_ulong();
    que.push(state);
    visited[stateId] = true;
    backtrack[stateId] = saveStateId;
}

void BFS(State start, State finish, vector<int>& backtrack)
{
    queue<State> que;
    vector<bool> visited(128);

    Push(que, visited, backtrack, start, 0);

    while (!que.empty())
    {
        State data = que.front();
        unsigned long saveStateId = data.to_ulong();

        if (!CheckBothAlive(data))
        {
            que.pop();
            continue;
        }

        if (data == finish)
        {
            break;
        }

        vector<State> moves;
        // one entity move
        for (int i = 0; i < Boat; ++i)
        {
            if (data[i] != data[Boat])
                continue;

            moves.push_back(State(1 << i));
        }

        // two entities move
        for (int i = 0; i < Boat; ++i)
        {
            for (int j = i + 1; j < Boat; ++j)
            {
                if (data[i] != data[Boat] || data[j] != data[Boat])
                    continue;

                moves.push_back(State((1 << i) | (1 << j)));
            }
        }

        for (State move : moves)
        {
            // toggle move, entities means they are moved to other side 
            State next(data ^ (move | State(1 << Boat)));
            int key = next.to_ulong();

            if (!visited[key] && CanControlBoat(move))
            {
                Push(que, visited, backtrack, next, saveStateId);
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