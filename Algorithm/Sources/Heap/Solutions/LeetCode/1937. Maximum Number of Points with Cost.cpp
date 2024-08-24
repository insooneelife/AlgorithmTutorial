#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
	long long maxPoints(vector<vector<int>>& points)
	{
		vector<vector<long long>> llpoints(points.size());
		for (int i = 0; i < points.size(); ++i)
		{
			for (int j = 0; j < points[i].size(); ++j)
			{
				llpoints[i].push_back(points[i][j]);
			}
		}

		for (int i = 0; i < llpoints.size() - 1; ++i)
		{
			vector<long long>& currentPoints = llpoints[i];
			vector<long long>& nextPoints = llpoints[i + 1];
			vector<bool> visited(currentPoints.size(), false);
			priority_queue<pair<int, long long>> pq;

			for (int j = 0; j < currentPoints.size(); ++j)
			{
				pq.push(make_pair(currentPoints[j], j));
			}


			while (!pq.empty())
			{
				const pair<int, long long>& item = pq.top();
				int current = item.second;
				int left = current - 1;
				int right = current + 1;

				pq.pop();

				if (left >= 0)
				{
					if (currentPoints[left] < currentPoints[current] - 1)
					{
						currentPoints[left] = currentPoints[current] - 1;
						visited[left] = true;
						pq.push(make_pair(currentPoints[left], left));
					}
				}

				if (right < currentPoints.size())
				{
					if (currentPoints[right] < currentPoints[current] - 1)
					{
						currentPoints[right] = currentPoints[current] - 1;
						visited[right] = true;
						pq.push(make_pair(currentPoints[right], right));
					}
				}
			}



			for (int j = 0; j < currentPoints.size(); ++j)
			{
				nextPoints[j] += currentPoints[j];
			}
		}

		long long maxVal = -1;
		int lastRow = llpoints.size() - 1;
		for (int j = 0; j < llpoints[lastRow].size(); ++j)
		{
			maxVal = std::max(maxVal, llpoints[lastRow][j]);
		}

		return maxVal;
	}


};
