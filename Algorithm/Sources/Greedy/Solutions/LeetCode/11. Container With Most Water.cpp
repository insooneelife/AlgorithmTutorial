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

// Two Pointers
// 시행착오
// 1. 문제를 너무 어렵게 생각함. DP로 접근함.
// 2. 정작 DP로 접근했는데 시간복잡도를 제대로 계산하지 않아 시간초과가 남

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
		int i = 0;
		int j = height.size() - 1;
		int maxArea = 0;

		while(i < j)
		{
			int leftH = height[i];
			int rightH = height[j];
			maxArea = std::max(maxArea, std::min(leftH, rightH) * (j - i));

			if(leftH < rightH)
			{
				i ++;
			}
			else if(leftH > rightH)
			{
				j--;
			}
			else
			{
				i++;
				j --;
			}
		}

		return maxArea;
	}


private:
};



int main()
{

	//vector<int> height = {1,8,6,2,5,4,8,3,7};

	vector<int> height = { 1,1 };
	

	Solution s;
	int ans = s.maxArea(height);
	
	std::cout << ans << std::endl;


	return 0;
}
