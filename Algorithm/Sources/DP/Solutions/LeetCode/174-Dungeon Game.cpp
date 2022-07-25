
// https://leetcode.com/problems/dungeon-game/
// 시행착오.
// 문제에서 hp가 초과되지 않는다는 조건에 대해 정확하게 설명해주지 않음.

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Solution {
public:

	int cache[201][201];

	int minHP(vector<vector<int>>& dungeon, int i, int j)
	{
		int n = dungeon.size();
		int m = dungeon[0].size();

		if (i >= n || j >= m)
			return std::numeric_limits<int>::max();

		if (i == n - 1 && j == m - 1)
			return 1 - min(dungeon[i][j], 0);

		if (cache[i][j] != 0)
			return cache[i][j];

		int right = minHP(dungeon, i + 1, j);
		int down = minHP(dungeon, i, j + 1);

		int hp = min(right, down);
		int ret;

		if (hp > dungeon[i][j])
			ret = hp - dungeon[i][j];
		else
			ret = 1;

		return cache[i][j] = ret;
	}

	int calculateMinimumHP(vector<vector<int>>& dungeon)
	{
		return minHP(dungeon, 0, 0);
	}
};


int main()
{
	Solution s;

	vector<vector<int>> dungeon =
	{
		{-2, -3, 3},
		{-5, -10, 1},
		{10, 30, -5 }
	};

	cout << s.calculateMinimumHP(dungeon);

	return 0;
}