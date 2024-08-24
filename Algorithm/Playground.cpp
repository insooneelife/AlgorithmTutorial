#include <iostream>
#include <vector>

using namespace std;


class Solution 
{
public:

	int stoneGameII(vector<int>& piles) 
	{
		int size = piles.size();

		for(int n = size - 1; n >= 0; --n)
		{
			for(int m = size; m >= 1; --m)
			{
				for(int t = 0; t < 2; ++t)
				{
					bool aliceTurn = (t == 1);

					int minmaxVal = 0;
					if(!aliceTurn)
					{
						minmaxVal = std::numeric_limits<int>::max();
					}

					for(int x = 1;  x <= 2 * m; ++x)
					{
						if (n + x > piles.size())
						{
							continue;
						}

						int val = dp[n + x][std::max(m, x)][!aliceTurn];

						if(aliceTurn)
						{
							int sum = val;
							for(int i = n; i < n + x; ++i)
							{
								sum += piles[i];
							}

							minmaxVal = std::max(minmaxVal, sum);
						}
						else
						{
							minmaxVal = std::min(minmaxVal, val);
						}
					}

					dp[n][m][aliceTurn] = minmaxVal;
				}
			}
		}

		//Print(piles.size());

		return dp[0][1][true];
	}


	void Print(int n) const
	{
		for(int i = 0; i < n; ++i)
		{
			for (int j = 1; j < n; ++j)
			{
				std::cout <<"(" << dp[i][j][0] << " " << dp[i][j][1] << ") ";
			}
			std::cout << std::endl;
		}
	}

private:
	int dp[101][101][2] = {};
};


int main()
{
	//vector<int> piles = { 2,7,9,4,4 };

	//vector<int> piles = {1, 2, 3, 4, 5, 100};
	vector<int> piles = { 1, 1, 1 };

	Solution s;
	cout << s.stoneGameII(piles);

	return 0;
}
