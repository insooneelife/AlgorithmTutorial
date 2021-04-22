// 카드 짝 맞추기 (조합 and 순열 and BFS)
// https://programmers.co.kr/learn/courses/30/lessons/72415

#include "STL.h"
#include "Utility.h"
#include "Algorithm.h"


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

const int N = 4;
const int MoveActions = 8;

struct Card
{
    Card() : type(0), i(0), j(0) {}
    Card(int type, int i, int j) : type(type), i(i), j(j) {}

    int Key() const { return i * N + j; }
    void Print() const { cout << "(" << type << "   " << i << " " << j << ") "; }

public:
    int type;
    int i;
    int j;
};

struct State
{
    State() : i(0), j(0), cost(0) {}
    State(int i, int j, int cost) : i(i), j(j), cost(cost) {}

    void Print() const { cout << "(" << i << " " << j << "   " << cost << ") "; }

public:
    int cost;
    int i;
    int j;
};

bool IsValid(int i, int j)
{
    return 0 <= i && i < N && 0 <= j && j < N;
}

void NextPos(const vector<vector<int>>& board, int si, int sj, int dir, int& i, int& j)
{
    vector<pair<int, int>> directions = { {1,0}, {0,1}, {-1,0}, {0,-1} };
    const int Directions = directions.size();

    if (dir < Directions)
    {
        i = si + directions[dir].first;
        j = sj + directions[dir].second;
        return;
    }

    int di = directions[dir - Directions].first;
    int dj = directions[dir - Directions].second;

    i = si;
    j = sj;
    while (true)
    {
        int ni = i + di;
        int nj = j + dj;

        if (!IsValid(ni, nj))
            break;

        i = ni;
        j = nj;

        if (board[i][j] > 0)
            break;
    }
}

int BFS(const vector<vector<int>>& board, int from_i, int from_j, int to_i, int to_j)
{
    queue<State> que;
    bool visited[N][N] = { 0 };
    int cost = 0;

    que.push(State(from_i, from_j, 0)); visited[from_i][from_j] = true;

    while (!que.empty())
    {
        State s = que.front();
        int i = s.i;
        int j = s.j;
        cost = s.cost;

        int ni, nj;

        // move actions
        for (int d = 0; d < MoveActions; ++d)
        {
            NextPos(board, i, j, d, ni, nj);
            if (IsValid(ni, nj) && !visited[ni][nj])
            {
                que.push(State(ni, nj, cost + 1));
                visited[ni][nj] = true;
            }
        }

        if (i == to_i && j == to_j)
        {
            break;
        }

        que.pop();
    }

    return cost;
}

void FindPairCard(const unordered_map<int, vector<Card>>& cards, const Card& card, Card& pair_card)
{
    vector<Card> type_cards = cards.at(card.type);

    for (int i = 0; i < type_cards.size(); ++i)
    {
        if (type_cards[i].Key() != card.Key())
        {
            pair_card = type_cards[i];
        }
    }
}


void Combinations(
    const unordered_map<int, vector<Card>>& cards,
    const vector<int>& card_types,
    int level,
    // copy this
    vector<Card> combs,
    vector<vector<Card>>& out_all_combs)
{
    if (level == card_types.size())
    {
        out_all_combs.push_back(combs);
        return;
    }

    vector<Card> type_cards = cards.at(card_types[level]);

    for (int i = 0; i < type_cards.size(); ++i)
    {
        combs.push_back(type_cards[i]);

        Card pair;
        FindPairCard(cards, type_cards[i], pair);
        combs.push_back(pair);

        Combinations(cards, card_types, level + 1, combs, out_all_combs);
        combs.pop_back();
        combs.pop_back();
    }
}

int CalcMoveCost(
    // copy this
    vector<vector<int>> board,
    const vector<Card>& combs)
{
    int sum_cost = 0;
    bool selected = false;

    for (int b = 0; b < combs.size() - 1; ++b)
    {
        Card from = combs[b];
        Card to = combs[b + 1];
        int cost = BFS(board, from.i, from.j, to.i, to.j);

        // flip card
        if (selected)
        {
            board[from.i][from.j] = 0;
            board[to.i][to.j] = 0;
        }

        selected = !selected;
        if (from.type > 0)
            cost++;

        sum_cost += cost;
    }
    return sum_cost + 1;
}

int CalcAllMoveCosts(const vector<vector<int>>& board, const vector<vector<Card>>& all_combs)
{
    int min_cost = numeric_limits<int>::max();
    for (int i = 0; i < all_combs.size(); ++i)
    {
        min_cost = min(CalcMoveCost(board, all_combs[i]), min_cost);
    }

    return min_cost;
}

int solution(vector<vector<int>> board, int r, int c)
{
    int answer = numeric_limits<int>::max();
    vector<int> card_types;
    unordered_map<int, vector<Card>> cards;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j] > 0)
            {
                int type = board[i][j];
                card_types.push_back(type);
                Card c(type, i, j);
                cards[type].push_back(c);
            }
        }
    }

    sort(begin(card_types), end(card_types));
    card_types.erase(unique(begin(card_types), end(card_types)), end(card_types));

    int cnt = 0;
    do
    {
        vector<vector<Card>> all_combs;
        Combinations(cards, card_types, 0, { Card(0, r, c) }, all_combs);

        int min_cost = CalcAllMoveCosts(board, all_combs);
        answer = min(answer, min_cost);
        cnt++;
    } while (std::next_permutation(begin(card_types), end(card_types)));

    return answer;
}


int main()
{
    int answer = 0;
    // case 1.
    // anwer : 14
    {
        int r = 1;
        int c = 0;
        vector<vector<int>> board = { {1, 0, 0, 3}, {2, 0, 0, 0}, {0, 0, 0, 2}, {3, 0, 1, 0} };
        answer = solution(board, r, c);
    }

    // case 2.
    // anwer : 16
    {
        int r = 0;
        int c = 1;
        vector<vector<int>> board = { {3,0,0,2}, {0,0,1,0}, {0,1,0,0}, {2,0,0,3 } };
        //answer = solution(board, r, c);
    }

    cout << answer << endl;

    return 0;
}




