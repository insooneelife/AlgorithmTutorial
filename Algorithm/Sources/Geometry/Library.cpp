#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <numbers>
#include <algorithm>
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

struct Line
{
	Vec from;
	Vec to;

	Line(Vec from, Vec to) : from(from), to(to) {}


	double length() const
	{
		Vec delta = to - from;
		return delta.len();
	}

	bool operator==(const Line& other) const
	{
		return equal(*this, other);
	}

	friend std::ostream& operator<<(std::ostream& os, const Line& line)
	{
		os << line.toString();
		return os;
	}

	std::string toString() const
	{
		std::ostringstream oss;
		oss << "(from: " << from.toString() << ", to: " << to.toString() << ")";
		return oss.str();
	}

	static bool equal(Line a, Line b)
	{
		return a.from == b.from && a.to == b.to;
	}

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
		double ccwa1 = Vec::cross(a.from, a.to, b.from);
		double ccwa2 = Vec::cross(a.from, a.to, b.to);

		if (ccwa1 == 0.0f && ccwa2 == 0.0f)
		{
			return pointOnLine(a, b.from) || pointOnLine(a, b.to);
		}

		double ccwb1 = Vec::cross(b.from, b.to, a.from);
		double ccwb2 = Vec::cross(b.from, b.to, a.to);


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



struct Rect
{
	Vec leftBottom;
	Vec rightTop;

	Rect(Vec leftBottom, Vec rightTop) : leftBottom(leftBottom), rightTop(rightTop) {}
	Rect(double left, double right, double top, double bottom) :leftBottom(left, bottom), rightTop(right, top) {}

	double left() const
	{
		return leftBottom.x;
	}

	double right() const
	{
		return rightTop.x;
	}

	double top() const
	{
		return rightTop.y;
	}

	double bottom() const
	{
		return leftBottom.y;
	}

	double width() const
	{
		return right() - left();
	}

	double height() const
	{
		return top() - bottom();
	}

	double area() const
	{
		return width() * height();
	}

	bool operator==(const Rect& other) const
	{
		return
			this->leftBottom == other.leftBottom &&
			this->rightTop == other.rightTop;
	}

	friend std::ostream& operator<<(std::ostream& os, const Rect& rect)
	{
		os << rect.toString();
		return os;
	}

	std::string toString() const
	{
		std::ostringstream oss;
		oss << "(leftBottom: " << leftBottom << ", rightTop: " << rightTop << ")";
		return oss.str();
	}

	static double intersectArea(const Rect& a, const Rect& b)
	{
		double overlapLeft = std::max(a.left(), b.left());
		double overlapRight = std::min(a.right(), b.right());
		double overlapTop = std::min(a.top(), b.top());
		double overlapBottom = std::max(a.bottom(), b.bottom());

		double overlapWidth = overlapRight - overlapLeft;
		double overlapHeight = overlapTop - overlapBottom;

		// Check for no overlap
		if (overlapWidth <= 0 || overlapHeight <= 0)
		{
			return 0.0;
		}

		// Calculate overlap area
		return overlapWidth * overlapHeight;
	}

	// true if line overlap
	static bool doesIntersect(const Rect& a, const Rect& b)
	{
		// Check if one rectangle is to the left of the other
		if (a.right() < b.left() || b.right() < a.left())
			return false;

		// Check if one rectangle is above the other
		if (a.bottom() > b.top() || b.bottom() > a.top())
			return false;

		// Rectangles neither to the left, right, nor above each other must intersect
		return true;
	}
};


struct Circle
{
	Vec center; 
	double radius;  

	Circle(const Vec& center, double radius) : center(center), radius(radius) {}

	double area() const
	{
		return std::numbers::pi * radius * radius;
	}

	bool contains(const Vec& point) const
	{
		Vec diff = center - point;  
		return diff.len() <= radius;  
	}

	static bool intersects(const Circle& a, const Circle& b)
	{
		Vec diff = a.center - b.center; 
		double distance = diff.len();  
		return distance < (a.radius + b.radius); 
	}

	// Generate a uniform random position within the circle
	Vec randomPosition() const
	{
		std::random_device rd;  // Obtain a random number from hardware
		std::mt19937 gen(rd()); // Seed the generator
		std::uniform_real_distribution<> dis(0, 1);  // Define the range

		double theta = dis(gen) * 2 * std::numbers::pi;  // Random angle
		double u = dis(gen);  // Random value between 0 and 1
		double r = sqrt(u) * radius;  // Adjust radius for uniform distribution

		// Convert polar coordinates to Cartesian, accounting for the circle's position
		double x = center.x + r * cos(theta);
		double y = center.y + r * sin(theta);

		return Vec(x, y);
	}
	
	bool operator==(const Circle& other) const
	{
		return center == other.center && radius == other.radius;
	}

	// Overload << operator for easy output
	friend std::ostream& operator<<(std::ostream& os, const Circle& circle)
	{
		os << circle.toString();
		return os;
	}

	// String representation for debugging
	std::string toString() const
	{
		std::ostringstream oss;
		oss << "Circle(center: " << center.toString() << ", radius: " << radius << ")";
		return oss.str();
	}
};