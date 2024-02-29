#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;

typedef long long int ll;

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

	static ll cross(Vec a, Vec b, Vec c)
	{
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}

	static bool equal(Vec a, Vec b)
	{
		return a.x == b.x && a.y == b.y;
	}
};

struct Line
{
	Vec from;
	Vec to;

	Line(Vec from, Vec to) : from(from), to(to) {}

	static bool pointOnLine(const Line& line, const Vec point)
	{
		if (Vec::equal(line.from, point) || Vec::equal(line.to, point))
		{
			return true;
		}

		Vec p2from = Vec::sub(line.from, point);
		Vec p2to = Vec::sub(line.to, point);
		int angle = Vec::angle(p2from, p2to);
		return angle == 180;
	}

	static bool intersects(const Line& a, const Line& b)
	{
		ll ccwa1 = Vec::cross(a.from, a.to, b.from);
		ll ccwa2 = Vec::cross(a.from, a.to, b.to);

		if (ccwa1 == 0.0f && ccwa2 == 0.0f)
		{
			return pointOnLine(a, b.from) || pointOnLine(a, b.to);
		}

		ll ccwb1 = Vec::cross(b.from, b.to, a.from);
		ll ccwb2 = Vec::cross(b.from, b.to, a.to);


		if (ccwa1 * ccwa2 <= 0.0f && ccwb1 * ccwb2 <= 0.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

enum Directions : int
{
	Up, Left, Down, Right, Count
};

class Solution
{
public:
	bool isSelfCrossing(vector<int> distance)
	{

		vector<tuple<Directions, Vec, Line>> directions;
		Vec current(0, 0);
		Vec next(0, 0);

		for (int i = 0; i < distance.size(); ++i)
		{
			Directions dir = (Directions)(i % (int)Directions::Count);
			int dist = distance[i];
			Vec dirVec(0, 0);

			if (dir == Directions::Up)
			{
				dirVec = Vec(0, dist);
			}
			else if (dir == Directions::Left)
			{
				dirVec = Vec(-dist, 0);
			}
			else if (dir == Directions::Down)
			{
				dirVec = Vec(0, -dist);
			}
			else
			{
				dirVec = Vec(dist, 0);
			}

			directions.push_back(make_tuple(dir, dirVec, Line(current, Vec::add(current, dirVec))));
			current = Vec::add(current, dirVec);
		}

		for (int i = 0; i < directions.size(); ++i)
		{
			if (i < 3)
			{
				continue;
			}

			Line a = get<2>(directions[i]);
			Line b = get<2>(directions[i - 3]);

			if (Line::intersects(a, b))
			{
				return true;
			}

			if (i < 4)
			{
				continue;
			}

			Line c = get<2>(directions[i - 4]);
			if (Line::intersects(a, c))
			{
				return true;
			}

			if (i < 5)
			{
				continue;
			}

			Line d = get<2>(directions[i - 5]);
			if (Line::intersects(a, d))
			{
				return true;
			}

		}

		return false;
	}
};

int main()
{
	Solution s;
	cout << s.isSelfCrossing({ 2,1,1,2 });

	return 0;
}
