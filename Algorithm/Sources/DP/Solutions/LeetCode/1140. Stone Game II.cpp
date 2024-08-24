// �������� 
// 1. ��ȭ���� �������� �������� ����� ��ȭ���� ����� �����
//	  ���� ���, F(N, M, T)�� ������ �� �ִ� ��찡 F(N - X, M', !T)�� ���·� ��ȭ���� ����ٰ� �����غ���.
//	  ��ȭ���� ����� ���ؼ� X�� M'�� ǥ���ؾ��ϴµ�, max ������ ���� ������ �� �� ���� ǥ���ϱⰡ ��ƴ�.
// 
// 2. ���� - �۷ι� ������ cache�� ����� ���, leetcode���� �׽�Ʈ���̽��� �������� �������� ���� ĳ�ð��� �̿��ϴ� �� ����.
//	  cache ������ Ŭ���� ������ ��� ���� ������
//
// 3. ��ȭ���� ���� �� Bob�� ������ ������ �ٸ����� ������ ī���õǸ� �ȵ�. 
//	  Alice�� ���� ����ϴµ����� ���� ������ ���� �����Ͽ� max���� ����ؾ� ��. (�� �κп��� ������ �־���)


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
