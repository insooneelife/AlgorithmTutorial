


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

	// ���� ������ ��ġ�� �� ���� ��ġ �� ���� �ö󰡸� ���� �����Ѵ�.
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

	// �� �� ���Ҹ� �����ϰ�, ������ ���Ҹ� �� ���� ��ġ �� �Ʒ��� �������� ���� �����Ѵ�.
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

			// ���� �ڽ� ��尡 ��� ���� ��庸�� ������ ���� ��ġ�� �����Ѵ�.
			if ((lChildIndex >= _heapSize || _bucket[lChildIndex] <= _bucket[index]) &&
				(rChildIndex >= _heapSize || _bucket[rChildIndex] <= _bucket[index]))
			{
				break;
			}

			// ���� �ڽ� ��� ��� ���� ��庸�� ū ���, �� ū �ڽİ� ��ü�Ѵ�.
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

