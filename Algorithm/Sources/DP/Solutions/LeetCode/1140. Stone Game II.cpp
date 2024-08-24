// 시행착오 
// 1. 점화식을 도착지를 기준으로 세우면 점화식을 만들기 어려움
//	  예를 들어, F(N, M, T)로 도달할 수 있는 경우가 F(N - X, M', !T)인 형태로 점화식을 만든다고 가정해보자.
//	  점화식을 만들기 위해서 X와 M'를 표현해야하는데, max 연산이 들어가기 때문에 이 두 값을 표현하기가 어렵다.
// 
// 2. 버그 - 글로벌 변수로 cache를 만드는 경우, leetcode에서 테스트케이스를 돌려쓰는 과정에서 이전 캐시값을 이용하는 것 같음.
//	  cache 변수는 클래스 변수로 잡는 것이 좋을듯
//
// 3. 점화식을 만들 때 Bob이 선택한 돌들은 앨리스의 점수로 카운팅되면 안됨. 
//	  Alice의 값을 계산하는데에선 현재 돌들의 값도 포함하여 max값을 계산해야 함. (이 부분에서 착오가 있었음)


#include <iostream>
#include <vector>

using namespace std;


class Solution 
{
public:

	Solution(): cache(101, std::vector<std::vector<int>>(101, std::vector<int>(2))) {}

	int stoneGameII(vector<int>& piles) 
	{
		return aliceMaximum(piles, 0, 1, true);
	}

	int aliceMaximum(const vector<int>& piles, int n, int m, bool aliceTurn)
	{
		if (n == piles.size())
		{
			return 0;
		}		

		if(cache[n][m][aliceTurn] > 0)
		{
			return cache[n][m][aliceTurn];
		}

		int minmaxVal = 0;
		if (!aliceTurn)
		{
			minmaxVal = std::numeric_limits<int>::max();
		}

		for (int x = 1; x <= 2 * m; ++x)
		{
			if(n + x > piles.size())
			{
				continue;
			}

			int prevval = aliceMaximum(piles, n + x, std::max(m, x), !aliceTurn);

			// max
			if(aliceTurn)
			{
				int sum = 0;
				for (int i = n; i < n + x; ++i)
				{
					sum += piles[i];
				}

				int val = sum + prevval;
				if(minmaxVal < val)
				{
					minmaxVal = val;
				}
			}
			// min
			else
			{
				int val = prevval;
				if (minmaxVal > val)
				{
					minmaxVal = val;
				}
			}
		}
		
		return cache[n][m][aliceTurn] = minmaxVal;
	}

private:
	std::vector<std::vector<std::vector<int>>> cache;
};


int main()
{
	//vector<int> piles = { 2,7,9,4,4 };

	vector<int> piles = {1, 2, 3, 4, 5, 100};
	//vector<int> piles = { 1, 1, 1 };

	Solution s;
	cout << s.stoneGameII(piles);

	return 0;
}
