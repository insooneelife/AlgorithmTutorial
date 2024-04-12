
#include <iostream>
using namespace std;


struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution
{
public:
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		int delay = 0;
		ListNode* dnode = head;
		ListNode* dprev = head;
		for (ListNode* node = head; node != nullptr; node = node->next)
		{
			if (delay >= n)
			{
				dprev = dnode;
				dnode = dnode->next;
			}

			delay++;
		}

		ListNode* newhead = nullptr;
		if (dprev == dnode)
		{
			newhead = dnode->next;
			delete dnode;

		}
		else
		{
			newhead = head;
			dprev->next = dnode->next;
			delete dnode;
		}

		return newhead;
	}

	void print(ListNode* head) const
	{
		for (ListNode* node = head; node != nullptr; node = node->next)
		{
			cout << node->val << " ";
		}
	}
};



int main()
{
	Solution sol;

	ListNode* node5 = new ListNode(5, nullptr);
	ListNode* node4 = new ListNode(4, node5);
	ListNode* node3 = new ListNode(3, node4);
	ListNode* node2 = new ListNode(2, nullptr);
	ListNode* node1 = new ListNode(1, node2);

	sol.removeNthFromEnd(node1, 1);

	return 0;
}
