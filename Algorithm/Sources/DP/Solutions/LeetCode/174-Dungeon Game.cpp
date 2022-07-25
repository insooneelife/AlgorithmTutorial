
// https://leetcode.com/problems/dungeon-game/

// 시행착오.
// 문제에서 hp가 초과되지 않는다는 조건에 대해 정확하게 설명해주지 않음.

// 문제풀이.
// i, j를 시작 위치로 하는 최소 요구 초기체력 = 
// min(i + 1, j 위치에서의 최소 요구 초기체력, i, j + 1 위치에서의 최소 요구 초기체력) => hp
// i, j 위치에서의 체력 변동량(dungeon[i][j])보다 hp가 크다면 변동량을 hp에 더해준다. (음수인 경우 요구체력이 늘어날 것이고, 양수인 경우 요구체력이 줄어들 것이다.)
// 반대로 hp가 작다면 요구 초기체력을 1로 세팅해준다. (dungeon[i][j]의 값이 10인데 그 다음단계로의 최소요구체력이 9이면 어차피 체력 1로도 충분히 클리어 가능하다.)

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