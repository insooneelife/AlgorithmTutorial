


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <bitset>
#include <functional>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <random>
#include <limits>
#include <numeric>
#include <cmath> // pow
#include <memory.h> // memset
#include <cassert>

using namespace std;
typedef long long ll;

class Heap
{
public:
	Heap(int bucketSize)
	:
	_bucket(bucketSize),
	_heapSize(0)
	{}

	// 힙의 마지막 위치에 새 원소 배치 후 위로 올라가며 힙을 복구한다.
	void Insert(int value) 
	{
		int index = _heapSize;
		_bucket[index] = value;
		_heapSize++;

		while(index > 0)
		{
			int parentIndex = (index - 1) / 2;
			int parentValue = _bucket[parentIndex];

			if (parentValue < value)
			{
				std::swap(_bucket[parentIndex], _bucket[index]);
			}

			index = parentIndex;
		}
	}

	// 맨 위 원소를 제거하고, 마지막 원소를 맨 위에 배치 후 아래로 내려가며 힙을 복구한다.
	int Delete()
	{
		assert(_heapSize > 0);

		_heapSize --;
		int ret = _bucket[0];
		_bucket[0] = _bucket[_heapSize];

		int index = 0;

		while(index < _heapSize)
		{
			int lChildIndex = (index + 1) * 2 - 1;
			int rChildIndex = (index + 1) * 2;

			if ((lChildIndex >= _heapSize || _bucket[lChildIndex] <= _bucket[index]) &&
				(rChildIndex >= _heapSize || _bucket[rChildIndex] <= _bucket[index]))
			{
				break;
			}

			if (lChildIndex < _heapSize && 
				rChildIndex < _heapSize &&
			    _bucket[lChildIndex] > _bucket[index] &&
				_bucket[rChildIndex] > _bucket[index])
			{
				if(_bucket[lChildIndex] > _bucket[rChildIndex])
				{
					swap(_bucket[index], _bucket[lChildIndex]);
					index = lChildIndex;
				}
				else
				{
					swap(_bucket[index], _bucket[rChildIndex]);
					index = rChildIndex;
				}
			}
			else if(lChildIndex < _heapSize && _bucket[lChildIndex] > _bucket[index])
			{
				swap(_bucket[index], _bucket[lChildIndex]);
				index = lChildIndex;
			}
			else if(rChildIndex < _heapSize && _bucket[rChildIndex] > _bucket[index])
			{
				swap(_bucket[index], _bucket[rChildIndex]);
				index = rChildIndex;
			}
			else
			{
				assert(false);
			}
		}

		return ret;
	}

	int Size() const { return _heapSize; }

	void Print() const
	{
		cout << _heapSize << "   ";
		for (int i = 0; i < _heapSize; ++i)
		{
			cout << _bucket[i] << " ";
		}
		cout << endl;
	}

private:

	vector<int> _bucket;
	int _heapSize;
};


class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) 
	{
		Heap heap(nums.size());
		for(int v : nums)
		{
			heap.Insert(v);
		}

		int value = 0;
		for(int i = 0; i < k; ++i)
		{
			value = heap.Delete();
		}

		return value;
	}
};


int main()
{
	Solution s;

	vector<int> nums = { 7,6,5,4,3,2,1 };
	int k = 5;

	int answer = s.findKthLargest(nums, k);
	
	cout << answer;

	return 0;
}

