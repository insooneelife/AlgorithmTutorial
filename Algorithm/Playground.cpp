/*

11. Container With Most Water
Medium 29371 1809

Add to List

Share
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.



Example 1:


Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1


Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104


*/

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:

	int maxArea(vector<int>& height) 
	{
		dp.assign(height.size(), 0);

		int n = height.size();
		
		for (int i = 0; i < height.size(); ++i)
		{
			
		}
	}

	void Print(int n) const
	{
		for (int i = 0; i < n; ++i)
		{
			std::cout << dp[i] <<" ";
		}
	}

private:

	vector<int> dp;
};



int main()
{

	vector<int> height = {1,8,6,2,5,4,8,3,7};

	//vector<int> height = { 1,1 };
	

	Solution s;
	int ans = s.maxArea(height);
	
	std::cout << ans << std::endl;


	return 0;
}
