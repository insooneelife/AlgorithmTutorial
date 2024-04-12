
#include <iostream>
#include <vector>
#include <array>
using namespace std;


class Solution 
{
public:
	int trap(vector<int>& height) 
	{
		int sumval = 0;
		int maxval = -1;
		int maxi = -1;
		for(int i = 0; i < height.size(); ++i)
		{
			int h = height[i];
			sumval += h;

			if(maxval < h)
			{
				maxval = h;
				maxi = i;
			}
		}

		int sum = 0;
		maxval = -1;
		for(int i = 0; i < maxi; ++i)
		{
			int h = height[i];
			if (maxval < h)
			{
				maxval = h;
			}

			sum += maxval;
		}

		maxval = -1;
		for (int i = height.size() - 1; i > maxi; --i)
		{
			int h = height[i];
			if (maxval < h)
			{
				maxval = h;
			}

			sum += maxval;
		}

		sum += height[maxi];

		return sum - sumval;
	}
};

int main()
{
	Solution s; 

	//vector<int> v = { 0,1,0,2,1,0,1,3,2,1,2,1 };
	vector<int> v = { 4,2,0,3,2,5 };

	cout << s.trap(v);

	return 0;
}
