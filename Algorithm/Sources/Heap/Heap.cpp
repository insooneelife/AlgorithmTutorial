


#include <iostream>
#include <vector>
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

		while (index > 0)
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

		_heapSize--;
		int ret = _bucket[0];
		_bucket[0] = _bucket[_heapSize];

		int index = 0;

		while (index < _heapSize)
		{
			int lChildIndex = (index + 1) * 2 - 1;
			int rChildIndex = (index + 1) * 2;

			// 양쪽 자식 노드가 모두 현재 노드보다 작으면 현재 위치에 정착한다.
			if ((lChildIndex >= _heapSize || _bucket[lChildIndex] <= _bucket[index]) &&
				(rChildIndex >= _heapSize || _bucket[rChildIndex] <= _bucket[index]))
			{
				break;
			}

			// 양쪽 자식 노드 모두 현재 노드보다 큰 경우, 더 큰 자식과 교체한다.
			if (lChildIndex < _heapSize &&
				rChildIndex < _heapSize &&
				_bucket[lChildIndex] > _bucket[index] &&
				_bucket[rChildIndex] > _bucket[index])
			{
				if (_bucket[lChildIndex] > _bucket[rChildIndex])
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
			else if (lChildIndex < _heapSize && _bucket[lChildIndex] > _bucket[index])
			{
				swap(_bucket[index], _bucket[lChildIndex]);
				index = lChildIndex;
			}
			else if (rChildIndex < _heapSize && _bucket[rChildIndex] > _bucket[index])
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


int main()
{

	Heap heap(10);
	heap.Insert(3);
	heap.Print();
	heap.Insert(2);
	heap.Print();
	heap.Insert(1);
	heap.Print();
	heap.Insert(5);
	heap.Print();
	heap.Insert(6);
	heap.Print();
	heap.Insert(4);
	heap.Print();

	while (heap.Size() > 0)
	{
		int value = heap.Delete();
		cout << "pop : " << value << endl;
		heap.Print();
	}

	return 0;
}

