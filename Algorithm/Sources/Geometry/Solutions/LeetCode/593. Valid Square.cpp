
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;


float clamp(float v, float lo, float hi)
{
	if (v < lo)
	{
		return lo;
	}

	if (v > hi)
	{
		return hi;
	}

	return v;
}

struct Vec
{
	int x;
	int y;

	Vec(int x, int y)
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

	static int dot(Vec a, Vec b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static float angle(Vec a, Vec b)
	{
		const float pi = 3.141592653589793;
		float cosine = (float)Vec::dot(a, b) / (Vec::len(a) * Vec::len(b));
		cosine = clamp(cosine, -1.0f, 1.0f);
		float angle = acos(cosine) * 180 / pi;
		return angle;
	}


	static float len(Vec a)
	{
		return sqrt(a.x * a.x + a.y * a.y);
	}

	static int cross(Vec a, Vec b, Vec c)
	{
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}
};

class Solution
{
public:
	bool validSquare(vector<int> p1, vector<int> p2, vector<int> p3, vector<int> p4)
	{
		vector<Vec> points =
		{
			Vec(p1[0], p1[1]), Vec(p2[0], p2[1]), Vec(p3[0], p3[1]), Vec(p4[0], p4[1])
		};

		// find lowest
		int minY = numeric_limits<int>::max();
		int minX = numeric_limits<int>::max();
		int minIndex = -1;
		for (int i = 0; i < points.size(); ++i)
		{
			if (minY > points[i].y)
			{
				minY = points[i].y;
				minX = points[i].x;
				minIndex = i;
			}
			else if (minY == points[i].y)
			{
				if (minX > points[i].x)
				{
					minY = points[i].y;
					minX = points[i].x;
					minIndex = i;
				}
			}
		}

		swap(points[0], points[minIndex]);

		vector<pair<float, Vec>> anglePoints;
		anglePoints.push_back(make_pair(0, points[0]));
		Vec right(1, 0);

		for (int i = 1; i < points.size(); ++i)
		{
			Vec to = Vec::sub(points[i], points[0]);
			float tolen = Vec::len(to);

			if (tolen == 0.0f)
				return false;

			float angle = Vec::angle(to, right);
			anglePoints.push_back(make_pair(angle, points[i]));
		}

		sort(begin(anglePoints) + 1, end(anglePoints),
			[](auto a, auto b) { return a.first < b.first; });

		for (int i = 0; i < anglePoints.size(); ++i)
		{
			Vec a = anglePoints[i].second;
			Vec b = anglePoints[(i + 1) % anglePoints.size()].second;
			Vec c = anglePoints[(i + 2) % anglePoints.size()].second;


			int cross = Vec::cross(a, b, c);
			if (cross <= 0)
			{
				return false;
			}

			Vec v = Vec::sub(a, b);
			Vec u = Vec::sub(c, b);

			float angle = Vec::angle(v, u);
			if (angle != 90.0f)
			{
				return false;
			}

			if (Vec::len(v) != Vec::len(u))
			{
				return false;
			}

			//cout << cross << " " << angle << endl;
		}

		return true;
	}
};

int main()
{
	Solution s;
	cout << s.validSquare({0, 0}, {1, 1}, {1, 0}, {0, 1});

	return 0;
}
