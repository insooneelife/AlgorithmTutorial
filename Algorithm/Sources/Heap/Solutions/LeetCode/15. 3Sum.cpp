/*
15. 3Sum
Medium 31132 2899

Add to List

Share
Given an integer array nums, return all the triplets[nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.



Example 1:

Input: nums = [-1, 0, 1, 2, -1, -4]
Output : [[-1, -1, 2], [-1, 0, 1]]
Explanation :
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are[-1, 0, 1] and [-1, -1, 2].
Notice that the order of the output and the order of the triplets does not matter.


Example 2:

Input: nums = [0, 1, 1]
Output : []
Explanation : The only possible triplet does not sum up to 0.


Example 3 :

Input : nums = [0, 0, 0]
Output : [[0, 0, 0]]
Explanation : The only possible triplet sums up to 0.


Constraints :

3 <= nums.length <= 3000
- 105 <= nums[i] <= 105
*/


// 시행착오
// 1. 바이너리 서치를 이용한 방법으로 lower_bound를 찾고, 찾은 위치부터 모든 해를 얻기 위한 작업에서 다음과 같은 해가 나오면 시간초과가 난다.
//	  vector<int> nums = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
//	  시간복잡도 계산 자체는 맞았는데, 예외를 보면 처음부터 슬라이딩 방식으로 탐색했으면 더 빠르게 해결할 수 있었다.

// 2. negative 컨테이너에 대해서도 abs를 한 후 정렬을 해주는 것이 안전하다.

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>

using namespace std;

class Solution
{
public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		set<vector<int>> answers;
		sort(nums.begin(), nums.end());

		int zeroCnt = 0;
		std::vector<int> positives;
		std::vector<int> negatives;

		for (int i = 0; i < nums.size(); ++i)
		{
			if (nums[i] >= 0)
			{
				positives.push_back(nums[i]);
				if (nums[i] == 0)
				{
					zeroCnt++;
				}
			}
			else
			{
				negatives.push_back(nums[i]);
			}
		}

		if (zeroCnt >= 3)
		{
			answers.insert({ 0, 0, 0 });
		}

		

		// make comb for 1, 2
		if (negatives.size() >= 1 && positives.size() >= 2)
		{
			Match(negatives, positives, answers);
		}

		// make comb for 2, 1		
		if (negatives.size() >= 2 && positives.size() >= 1)
		{
			Match(positives, negatives, answers);
		}

		vector<vector<int>> vanswers;
		for(const auto& e : answers)
		{
			vanswers.push_back(e);
		}

		return vanswers;
	}

	void Match(const vector<int>& psingles, const vector<int>& pairs, set<vector<int>>& answers)
	{
		vector<std::tuple<int, int>> singles;
		for(int i = 0; i < psingles.size(); ++i)
		{
			singles.push_back(make_tuple(abs(psingles[i]), psingles[i]));
		}
		sort(begin(singles), end(singles), [](const auto& a, const auto& b){ 
			return get<0>(a) < get<0>(b);
		});


		std::vector<tuple<int, int, int>> combs;
		for (int i = 0; i < pairs.size(); ++i)
		{
			for (int j = i + 1; j < pairs.size(); ++j)
			{
				combs.push_back(make_tuple(std::abs(pairs[i] + pairs[j]), pairs[i], pairs[j]));
			}
		}

		std::sort(begin(combs), end(combs), [](const auto& a, const auto& b){
			return std::get<0>(a) < get<0>(b);
		});


		int i = 0;
		int j = 0;
		while(i < combs.size() && j < singles.size())
		{
			int combTarget = abs(get<0>(combs[i]));
			int singleTarget = get<0>(singles[j]);
			if(combTarget > singleTarget)
			{
				j ++;
			}
			else if (combTarget < singleTarget)
			{
				i ++;
			}
			else
			{
				vector<int> v = { get<1>(singles[j]), get<1>(combs[i]), get<2>(combs[i]) };
				sort(begin(v), end(v));
				answers.insert(v);
				i ++;
			}
		}
	}


	void Print(const vector<vector<int>>& answers) const
	{
		for (int i = 0; i < answers.size(); ++i)
		{
			for (int j = 0; j < answers[i].size(); ++j)
			{
				std::cout << answers[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};



int main()
{

	//vector<int> nums = { -1,0,1,2,-1,-4 };

	//vector<int> nums = {-2, 0, 1, 1, 2};


	vector<int> nums = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	//vector<int> nums = { 3, 0, -2, -1, 1, 2 };

	

	Solution s;
	const auto& ans = s.threeSum(nums);
	s.Print(ans);

	return 0;
}
