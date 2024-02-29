#include <iostream>
#include <vector>
#include <random>
#include <numbers>
#include <sstream>
using namespace std;



struct Vec
{
	double x;
	double y;

	Vec(double x, double y)
		:x(x), y(y)
	{}

	Vec operator+(const Vec& other) const
	{
		return add(*this, other);
	}

	Vec operator-(const Vec& other) const
	{
		return sub(*this, other);
	}

	Vec operator*(double k) const
	{
		return mul(*this, k);
	}

	bool operator==(const Vec& other) const
	{
		return equal(*this, other);
	}

	double operator*(const Vec& other) const
	{
		return dot(*this, other);
	}

	bool operator<(const Vec& other) const
	{
		if (y == other.y)
		{
			return x < other.x;
		}
		return y < other.y;
	}

	double len() const
	{
		return len(*this);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec& vec)
	{
		os << vec.toString();
		return os;
	}

	std::string toString() const
	{
		std::ostringstream oss;
		oss << "(" << x << ", " << y << ")";
		return oss.str();
	}


	static Vec add(Vec a, Vec b)
	{
		return Vec(a.x + b.x, a.y + b.y);
	}

	static Vec sub(Vec a, Vec b)
	{
		return Vec(a.x - b.x, a.y - b.y);
	}

	static Vec mul(Vec a, double k)
	{
		return Vec(a.x * k, a.y * k);
	}

	static Vec absolute(Vec p)
	{
		return Vec(abs(p.x), abs(p.y));
	}

	static double dot(Vec a, Vec b)
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

	static double cross(Vec a, Vec b, Vec c)
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
	vector<vector<int>> kClosest(vector<vector<int>>& points, int k) 
	{
		vector<Vec> vectors;
		for(int i = 0; i < points.size(); ++i)
		{
			Vec v(points[i][0], points[i][1]);
			vectors.push_back(v);
		}

		sort(begin(vectors), end(vectors), [](const Vec& a, const Vec& b) { return a.len() < b.len(); });

		vector<vector<int>> outputs;
		for(auto e : vectors)
		{
			outputs.push_back({(int)e.x, (int)e.y});
			if(--k <= 0)
			{
				break;
			}
		}

		return outputs;
	}
};


int main()
{
	vector<vector<int>> circles { {3,3} ,{5,-1},{-2,4} };
	Solution sol;
	sol.kClosest(circles, 2);

	return 0;
}
