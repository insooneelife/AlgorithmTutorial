#include <algorithm>
#include <vector>
using namespace std;


class Solution 
{
public:
	int threeSumClosest(vector<int>& nums, int target)
	{
		vector<int> lefts;
		vector<int> rights;
		for(int i = 0; i < nums.size(); ++i)
		{
			nums[i] -= target;

			if(nums[i] <= 0)
			{
				lefts.push_back(nums[i]);
			}
			else
			{
				rights.push_back(nums[i]);
			}
		}

		sort(begin(lefts), end(lefts), greater());
		sort(begin(rights), end(rights), greater());

		if(lefts.size() == 0)
		{
			return rights[0] + rights[1] + rights[2] + target * 3;
		}
		else if(rights.size() == 0)
		{
			return lefts[0] + lefts[1] + lefts[2] + target * 3;
		}
		else
		{
			// 2, 1			
			for(int i = 0; i < lefts.size(); ++i)
			{
				for (int j = i + 1; j < lefts.size(); ++j)
				{
					lefts[i] + lefts[j];
				}
			}
			

			// 1, 2
			{
			}
		}
	}
};


int main()
{
	[4, 0, 5, -5, 3, 3, 0, -4, -5]
	-2

	return 0;
}
