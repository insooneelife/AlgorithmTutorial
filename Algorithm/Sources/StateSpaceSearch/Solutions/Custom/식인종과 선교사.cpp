/*
문제.
m명의 선교사와 m명의 식인종이 나룻배를 타고 강을 건너려고 하는데, 
나룻배에는 n명 밖에는 탈 수가 없다. 
만일 강의 어느 쪽에서라도 식인종의 수가 선교사의 수보다 많으면 식인종들은 선교사들을 잡아먹게 된다.
이 때 선교사들이 잡혀먹히지 않고 무사히 강을 건너려면 어떻게 해야 하는가?
*/



// 시행착오
// 1. CheckAlive를 현재 노드에 대해 사용하고 있었음. next_node에 대해 이용해야함

#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>

using namespace std;


struct State
{
    State() : human(0), cannibal(0), boat(false) {}
    State(int human, int cannibal, bool boat)
        : human(human), cannibal(cannibal), boat(boat)
    {}

    State OppositeState(const int kHumans, const int kCannibal) const
    {
        return State(kHumans - human, kCannibal - cannibal, !boat);
    }

    long long Key() const
    {
        return (long long)boat * 100000LL * 100000LL + (long long)cannibal * 100000LL + (long long)human;
    }

    void Print() const
    {
        cout << "human : " << human << " cannibal : " << cannibal << " boat : " << boat << endl;
    }

public:
    // 왼쪽 섬 데이터
    int human;
    int cannibal;
    bool boat;
};


struct Node
{
    Node() : state(), level(0), forward(false) {}
    Node(State state, int level, bool forward) : state(state), level(level), forward(forward) {}

    void Print() const
    {
        state.Print();
        cout << "level : " << level << "  forward : " << forward << endl << endl;
    }

public:
    State state;
    int level;
    bool forward;
};


class RiverCrossing
{
public:
    RiverCrossing(const int kHumans, const int kCannibal, const int kBoats)
        :
        kHumans(kHumans), kCannibal(kCannibal), kBoats(kBoats)
    {}

    bool BidirectionalBFS(Node& forward, Node& backward)
    {
        State start(kHumans, kCannibal, true);
        State finish = start.OppositeState(kHumans, kCannibal);
        bool found = false;
        
        Push(Node(start, 0, true));
        Push(Node(finish, 0, false));

        while (!que.empty())
        {
            Node node = que.front();
            State state = node.state;
            que.pop();

            //node.Print();
            if (Cross(node, forward, backward))
            {
                found = true;
                break;
            }
        }

        return found;
    }

private:

    bool Cross(const Node& node, Node& next_node, Node& visited_node)
    {
        State state = node.state;
        int level = node.level;
        bool forward = node.forward;
        int sign = state.boat ? -1 : 1;

        for (int h = 0; h <= kBoats; h++)
        {
            for (int c = 0; c <= kBoats; c++)
            {
                if (h == 0 && c == 0)
                    continue;

                if (h + c > kBoats)
                    continue;

                int move_human = h * sign;
                int move_cannibal = c * sign;

                State next(state.human + move_human, state.cannibal + move_cannibal, !state.boat);
                next_node = Node(next, level + 1, forward);

                // 생존 예외처리
                if (!CheckAlive(next))
                {
                    continue;
                }

                // 경계 값 예외처리
                if (next.human < 0 || next.cannibal < 0 ||
                    next.human > kHumans || next.cannibal > kCannibal)
                {
                    continue;
                }

                // 방문 예외처리
                if (visited.find(next.Key()) != visited.end())
                {
                    visited_node = visited[next.Key()];

                    if (forward != visited_node.forward)
                    {
                        return true;
                    }

                    continue;
                }

                // 배 위에서의 예외처리
                if (c > h && h > 0)
                {
                    continue;
                }

                Push(next_node);
            }
        }

        return false;
    }

    void Push(const Node& node)
    {
        que.push(node);
        visited.insert(make_pair(node.state.Key(), node));
    }

    bool CheckBothAlive(const State& state) const
    {
        if (state.cannibal > state.human && state.human > 0)
        {
            return false;
        }
        return true;
    }

    bool CheckAlive(const State& state) const
    {
        return CheckBothAlive(state) && CheckBothAlive(state.OppositeState(kHumans, kCannibal));
    }

private:
    const int kHumans;
    const int kCannibal;
    const int kBoats;

    queue<Node> que;
    map<long long, Node> visited;
};





int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int m, n;
        cin >> m >> n;

        RiverCrossing rc(m, m, n);

        Node forward;
        Node backward;
        bool found = rc.BidirectionalBFS(forward, backward);

        //forward.Print();
        //backward.Print();

        if (found)
        {
            cout << forward.level + backward.level << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    return 0;
}