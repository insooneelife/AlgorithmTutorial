
#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct TreeNode 
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution
{
public:
	bool testSequence(int level, const vector<int>& sequence)
	{
		if (level % 2 == 0)
		{
			for (int i = 0; i < sequence.size(); ++i)
			{
				if (sequence[i] % 2 != 1)
				{
					return false;
				}
			}

			// check increasing
			int prev = numeric_limits<int>::min();
			for (int i = 0; i < sequence.size(); ++i)
			{
				if (prev >= sequence[i])
				{
					return false;
				}
				prev = sequence[i];
			}
		}
		else
		{
			for (int i = 0; i < sequence.size(); ++i)
			{
				if (sequence[i] % 2 != 0)
				{
					return false;
				}
			}

			// check decreasing
			int prev = numeric_limits<int>::max();
			for (int i = 0; i < sequence.size(); ++i)
			{
				if (prev <= sequence[i])
				{
					return false;
				}
				prev = sequence[i];
			}
		}

		return true;
	}

	bool isEvenOddTree(TreeNode* root)
	{
		queue<pair<TreeNode*, int>> que;
		int prevLevel = 0;
		vector<int> sequence;

		que.push(make_pair(root, 0));

		while (!que.empty())
		{
			auto p = que.front();
			que.pop();
			TreeNode* node = p.first;
			int level = p.second;

			if (prevLevel == level)
			{
				sequence.push_back(node->val);
			}
			else
			{
				if (!testSequence(prevLevel, sequence))
				{
					return false;
				}

				sequence.clear();
				sequence.push_back(node->val);
				prevLevel = level;
			}


			if (node->left != nullptr)
			{
				que.push(make_pair(node->left, level + 1));
			}

			if (node->right != nullptr)
			{
				que.push(make_pair(node->right, level + 1));
			}
		}

		if (sequence.size() > 0)
		{
			return testSequence(prevLevel, sequence);
		}
		else
		{
			return true;
		}
	}
};


int main()
{
	Solution s;

	
	TreeNode* ll = new TreeNode(3);
	TreeNode* lr = new TreeNode(3);
	TreeNode* rl = new TreeNode(7);
	TreeNode* l = new TreeNode(2, ll, lr);
	TreeNode* r = new TreeNode(4, rl, nullptr);
	TreeNode* root = new TreeNode(5, l, r);

	cout << s.isEvenOddTree(root);

	return 0;
}
