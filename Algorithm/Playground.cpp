
#include <iostream>
#include <vector>
#include <array>
using namespace std;

const int A = 0;
const int L = 1;
const int P = 2;


class Solution 
{
public:
	int F(int n, int slast, int last, int cnt)
	{
		

		if(n == 2)
		{
			if(slast == A && last == A)
			{
				return 0;
			}
			else
			{
				int countA = 0;
				if (slast == A)
				{
					countA++;
				}

				if (last == A)
				{
					countA++;
				}

				if (countA != cnt)
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
		}

		cout << endl;
		int sum = 0;
		for(int sslast = 0; sslast <= P; ++sslast)
		{
			if(sslast == L && slast == L && last == L)
			{
				continue;
			}

			for(int pcnt = 0; pcnt <= 1; ++pcnt)
			{				
				int cntA = 0;
				if(last == A)
					cntA ++;
				cntA += pcnt;

				if(cnt == cntA)
				{
					int val = F(n - 1, sslast, slast, pcnt);
					sum += val;
					cout << n - 1 << " " << (char)(sslast + 'A') << " " << (char)(slast + 'A') << " " << (char)(last + 'A') << " cnt : " << cnt << " " << cntA << " " << pcnt << " val : " << val << " sum : " << sum << endl;
				}
			}
		}

		return sum;		
	}

	int checkRecord(int n) 
	{
		int sum = 0;
		for (int i = 0; i <= P; ++i)
		{
			for (int j = 0; j <= P; ++j)
			{
				for (int pcnt = 0; pcnt <= 1; ++pcnt)
				{
					int o = F(n, i, j, pcnt);
					sum += o;
				}
			}
		}

		return sum;
	}
};

int main()
{
	Solution s; 

	cout << s.checkRecord(3);

	return 0;
}
