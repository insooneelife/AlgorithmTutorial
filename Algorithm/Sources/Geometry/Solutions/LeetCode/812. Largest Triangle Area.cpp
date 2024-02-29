// float으로 하면 오차로 문제 생김
// double로 바꾸고 나서 오차 제거

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <numbers>
#include <algorithm>

using namespace std;

typedef long long int ll;



struct Vec
{
	ll x;
	ll y;

	Vec(ll x, ll y)
		:x(x), y(y)
	{}

	static Vec add(Vec a, Vec b)
	{
		return Vec(a.x + b.x, a.y + b.y);
	}

	static Vec sub(Vec a, Vec b)
	{
		return Vec(a.x - b.x, a.y - b.y);
	}

	static ll dot(Vec a, Vec b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static double cosine(Vec a, Vec b)
	{
		double cos = (double)Vec::dot(a, b) / (Vec::len(a) * Vec::len(b));
		cos = clamp(cos, -1.0, 1.0);
		return cos;
	}

	static double angle(Vec a, Vec b)
	{
		double angle = acos(cosine(a, b)) * 180 / std::numbers::pi;
		return angle;
	}

	static double len(Vec a)
	{
		return sqrt(a.x * a.x + a.y * a.y);
	}

	static ll cross(Vec a, Vec b, Vec c)
	{
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}

	static bool equal(Vec a, Vec b)
	{
		return a.x == b.x && a.y == b.y;
	}
};


class Solution 
{
public:
	double largestTriangleArea(vector<vector<int>>& points) 
	{
		double maxArea = 0.0f;
		for(int i = 0; i < points.size(); ++i)
		{
			for (int j = i + 1; j < points.size(); ++j)
			{
				for (int k = j + 1; k < points.size(); ++k)
				{
					Vec a(points[i][0], points[i][1]);
					Vec b(points[j][0], points[j][1]);
					Vec c(points[k][0], points[k][1]);

					Vec toA = Vec::sub(a, b);
					Vec toC = Vec::sub(c, b);

					double cos = Vec::cosine(toA, toC);
					double sin = sqrt(1 - cos * cos);

					if(sin > 0.0f)
					{
						double area = Vec::len(toA) * Vec::len(toC) * sin / 2.0f;
						maxArea = max(maxArea, area);
					}
				}
			}

		}

		return maxArea;
	}
};

int main()
{
	Solution s;

	//vector<vector<int>> points = {{0, 0}, {0, 1}, {1, 0}, {0, 2}, {2, 0}};
	//vector<vector<int>> points = { {1, 0}, {0, 0}, {0, 1} };

	// float x, double o
	vector<vector<int>> points = { {- 21, 28} ,{- 30, -49},{-48, 47},{-22, -20},{19, 3},{5, 48}};
	
	cout << s.largestTriangleArea(points);

	return 0;
}
