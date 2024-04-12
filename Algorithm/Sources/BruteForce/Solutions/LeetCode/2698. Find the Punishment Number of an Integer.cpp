



#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <bitset>
using namespace std;

class Solution
{
public:

	bool checkAllCombs(const string& num, int val)
	{
		if (num.size() == 1)
		{
			return stoi(num) == val;
		}

		int len = num.size() - 1;
		int n = 1 << len;

		for (int i = 1; i < n; ++i)
		{
			bitset<8> bit(i);
			int sum = 0;
			int from = 0;

			for (int j = 0; j < len; ++j)
			{
				if (bit[j])
				{
					int to = j + 1;
					int part = stoi(num.substr(from, to - from));
					sum += part;
					from = to;
				}
			}

			sum += stoi(num.substr(from, num.size()));
			if (sum == val)
			{
				return true;
			}
		}

		return false;
	}

	int punishmentNumber(int n)
	{
		int sum = 0;
		for (int i = 1; i <= n; ++i)
		{
			int sq = i * i;
			string num = to_string(sq);
			if (checkAllCombs(num, i))
			{
				sum += sq;
			}
		}

		return sum;
	}
};

int main()
{
	Solution sol;

	cout << sol.punishmentNumber(37);

	return 0;
}
