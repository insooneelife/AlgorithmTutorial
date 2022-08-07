


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
#include <chrono>
#include <iomanip>
#include <random>
#include <limits>
#include <numeric>
#include <cmath> // pow
#include <memory.h> // memset


using namespace std;

typedef long long ll;

struct State
{
	int i;
	int j;
};

struct Node
{
public:
	Node(State state, ll costs) : state(state), costs(costs) {}

	bool operator<(Node other) const
	{
		return costs > other.costs;
	}

public:
	State state;
	ll costs;
};

static bool InArray2D(int rows, int columns, int i, int j)
{
	return
		0 <= i && i < rows &&
		0 <= j && j < columns;
}

ll BestFirstSearch(const vector<vector<int>>& board, State start, State finish, const ll BlockSymbol = 1, const ll EmptyCost = 0, const ll BlockCost = 1)
{
	const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	const int Rows = board.size();
	const int Columns = board[0].size();

	vector<vector<bool>> visited(Rows, vector<bool>(Columns, false));

	priority_queue<Node> pque;
	ll all = 0;
	Node node(start, 1);

	visited[start.i][start.j] = true;
	pque.push(node);

	while (!pque.empty())
	{
		node = pque.top();
		State state = node.state;
		ll costs = node.costs;
		int i = state.i;
		int j = state.j;

		if (i == finish.i && j == finish.j)
		{
			all = costs;
			break;
		}

		for (auto d : directions)
		{
			int nexti = i + d.first;
			int nextj = j + d.second;

			if (!InArray2D(Rows, Columns, nexti, nextj))
				continue;

			bool isBlocked = (board[nexti][nextj] == BlockSymbol);
			ll cost = isBlocked ? BlockCost : EmptyCost;

			if (!visited[nexti][nextj])
			{
				pque.push({ {nexti, nextj}, costs + cost });
				visited[nexti][nextj] = true;
			}
		}
		pque.pop();
	}
	return all;
}


vector<vector<int>> board;

int main()
{
	int n, m;

	cin >> n >> m;

	board.resize(n);

	for (int i = 0; i < n; ++i)
	{
		board[i].resize(m);

		char c;
		for (int j = 0; j < m; ++j)
		{
			cin >> c;

			int val = c - '0';
			board[i][j] = val;
		}
	}

	ll BlockCost = 10000000;
	ll val = BestFirstSearch(board, { 0,0 }, { n - 1, m - 1 }, 1, 1, BlockCost);

	if (val < BlockCost * 2)
	{
		ll emptyCost = val % BlockCost;
		ll blockCost = val / BlockCost;

		cout << emptyCost + blockCost + 1;
	}
	else
	{
		cout << -1;
	}

	return 0;
}