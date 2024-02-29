
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Point
{
	int x;
	int y;

	Point(int x, int y) : x(x), y(y) {}

	static Point add(Point a, Point b)
	{
		return Point(a.x + b.x, a.y + b.y);
	}

	static Point sub(Point a, Point b)
	{
		return Point(a.x - b.x, a.y - b.y);
	}

	static Point mul(Point a, int k)
	{
		return Point(a.x * k, a.y * k);
	}

	static Point absolute(Point p)
	{
		return Point(abs(p.x), abs(p.y));
	}

	static Point shrink(Point p)
	{
		if (p.x == 0 && p.y == 0)
		{
			cout << "error";
			return Point(0, 0);
		}

		if (p.x == 0)
		{
			return Point(0, 1);
		}

		if (p.y == 0)
		{
			return Point(1, 0);
		}

		Point ap = absolute(p);
		if (ap.x <= ap.y)
		{
			if (ap.y % ap.x == 0)
			{
				p = Point(1, p.y / p.x);
			}
		}
		else
		{
			if (ap.x % ap.y == 0)
			{
				p = Point(p.x / p.y, 1);
			}
		}

		if (p.x < 0)
		{
			p = Point::mul(p, -1);
		}

		return p;
	}

	string toString() const
	{
		return "(" + to_string(x) + " " + to_string(y) + ")";
	}
};

class Solution
{
public:
	bool testMod(int a, int mod)
	{
		if (mod == 0)
		{
			return a == 0;
		}

		return a % mod == 0;
	}

	bool testDivide(Point test, Point shrink)
	{
		if (shrink.x == 0 || shrink.y == 0)
		{
			return true;
		}

		return (test.x / shrink.x) == (test.y / shrink.y);
	}

	int maxPoints(vector<vector<int>>& points)
	{
		if (points.size() < 2)
		{
			return 1;
		}

		int maxCnt = 0;
		for (int i = 0; i < points.size(); ++i)
		{
			for (int j = 0; j < points.size(); ++j)
			{
				if (i == j)
					continue;

				Point origin(points[i][0], points[i][1]);
				Point other(points[j][0], points[j][1]);
				Point vector = Point::sub(other, origin);
				Point shrink = Point::shrink(vector);
				int cnt = 2;

				for (int k = 0; k < points.size(); ++k)
				{
					if (i == k || j == k)
						continue;

					Point test(points[k][0], points[k][1]);
					test = Point::sub(test, origin);

					if (testMod(test.x, shrink.x) &&
						testMod(test.y, shrink.y) &&
						testDivide(test, shrink))
					{
						cnt++;


					}
				}
				maxCnt = max(maxCnt, cnt);
			}
		}

		return maxCnt;
	}
};

int main()
{
	Solution s;

	vector<vector<int>> v = { {1,1} ,{3,2},{5,3},{4,1},{2,3},{1,4} };

	cout << s.maxPoints(v);

	return 0;
}
