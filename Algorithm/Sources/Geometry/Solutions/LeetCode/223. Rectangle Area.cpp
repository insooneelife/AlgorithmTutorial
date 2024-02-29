
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rect
{
	int x1;
	int x2;
	int y1;
	int y2;

	Rect(int x1, int x2, int y1, int y2)
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
	}

	int size() const
	{
		return (x2 - x1) * (y2 - y1);
	}

	void print()
	{
		cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
	}
};

class Solution 
{
public:
	int calcOverlapX(Rect a, Rect b)
	{
		if (a.x1 > b.x1)
		{
			swap(a, b);
		}

		if (a.x2 <= b.x1)
		{
			return 0;
		}

		return min(a.x2, b.x2) - b.x1;
	}

	int calcOverlapY(Rect a, Rect b)
	{
		if (a.y1 > b.y1)
		{
			swap(a, b);
		}

		if (a.y2 <= b.y1)
		{
			return 0;
		}

		return min(a.y2, b.y2) - b.y1;
	}


	int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) 
	{
		Rect a(ax1, ax2, ay1, ay2);
		Rect b(bx1, bx2, by1, by2);

		int overlapX = calcOverlapX(a, b);
		int overlapY = calcOverlapY(a, b);

		return a.size() + b.size() - overlapX * overlapY;
	}
};

int main()
{
	Solution s;
	cout << s.computeArea(-3, 0, 3, 4, 0, -1, 9, 2);

	return 0;
}
