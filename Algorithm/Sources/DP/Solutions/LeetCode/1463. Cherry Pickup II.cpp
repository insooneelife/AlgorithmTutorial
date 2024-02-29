


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
#include <cassert>

using namespace std;
typedef long long ll;

const int Max = numeric_limits<int>::max();
const int Min = numeric_limits<int>::min();

int cache[71][71][71];

class Solution 
{
public:
	int cherryPickup(vector<vector<int>>& grid) 
	{
		Cols = grid[0].size();
		Rows = grid.size();
		
		return DPArray(grid);
		
	}

	int DPArray(vector<vector<int>>& grid)
	{
		for (int r = 0; r < Cols; ++r)
		{
			for (int l = 0; l < Cols; ++l)
			{
				if(r == 0 && l == Cols - 1)
				{
					cache[0][r][l] = grid[0][r] + grid[0][l];
				}
				else
				{
					cache[0][r][l] = Min;					
				}
			}
		}

		for(int row = 1; row < Rows; ++row)
		{
			int prevRow = row - 1;
			for(int r = 0; r < Cols; ++r)
			{
				for(int l = 0; l < Cols; ++l)
				{
					int maxValue = Min;
					for (int i = -1; i <= 1; ++i)
					{
						for (int j = -1; j <= 1; ++j)
						{
							if (!IsValid(grid, r + i, prevRow) ||
								!IsValid(grid, l + j, prevRow))
							{
								continue;
							}

							int value = 0;
							if (r != l)
							{
								value = grid[row][r] + grid[row][l] + cache[prevRow][r + i][l + j];
							}
							else
							{
								value = grid[row][r] + cache[prevRow][r + i][l + j];
							}

							maxValue = max(maxValue, value);							
						}
					}

					//cout << "row : " << row << "  r : " << r << "  l : " << l << "  val : " << maxValue << endl;
					cache[row][r][l] = maxValue;
				}
			}			
		}

		int maxValue = Min;
		for (int r = 0; r < Cols; ++r)
		{
			for (int l = 0; l < Cols; ++l)
			{
				int value = cache[Rows - 1][r][l];
				maxValue = max(maxValue, value);
			}
		}

		return maxValue;
	}

	bool IsValid(vector<vector<int>>& grid, int column, int row) const
	{
		return 0 <= column && column < Cols && 
			   0 <= row && row < Rows;
	}

	void PrintCache() const
	{
		for(int row = 0; row < Rows; ++row)
		{
			for (int r = 0; r < Cols; ++r)
			{
				for (int l = 0; l < Cols; ++l)
				{
					cout << "(row : " << row << "  r : " << r << "  l : " << l << "  val : " << cache[row][r][l] <<endl;;
				}
			}
			cout << endl;
		}
	}

	int Cols;
	int Rows;

};

int main()
{
	Solution s;

	//vector<vector<int>> grid = {{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}};
	vector<vector<int>> grid = {{1, 0, 0, 0, 0, 0, 1}, {2, 0, 0, 0, 0, 3, 0}, {2, 0, 9, 0, 0, 0, 0}, {0, 3, 0, 5, 4, 0, 0}, {1, 0, 2, 3, 0, 0, 6}};
	//vector<vector<int>> grid = {{4, 1, 5, 7, 1}, {6, 0, 4, 6, 4}, {0, 9, 6, 3, 5}};

	int answer = s.cherryPickup(grid);

	std::cout << answer;

	return 0;
}

