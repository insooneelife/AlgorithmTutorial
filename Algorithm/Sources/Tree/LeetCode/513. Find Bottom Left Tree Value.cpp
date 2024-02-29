
#include <iostream>
#include <vector>
#include <map>

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

	void traverse(TreeNode* root, int level)
	{
		if (root == nullptr)
		{
			return;
		}

		if(maxlevel < level)
		{
			maxlevel = level;
			ans = root->val;
		}

		traverse(root->left, level + 1);
		traverse(root->right, level + 1);
	}

	int findBottomLeftValue(TreeNode* root) 
	{
		traverse(root, 0);
		return ans;
	}

	int ans = 0;
	int maxlevel = -1;

};


int main()
{
	Solution s;

	TreeNode* rll = new TreeNode(7);

	TreeNode* ll = new TreeNode(4);
	TreeNode* rl = new TreeNode(5, rll, nullptr);
	TreeNode* rr = new TreeNode(6);
	TreeNode* l = new TreeNode(2, ll, nullptr);
	TreeNode* r = new TreeNode(3, rl, rr);
	TreeNode* root = new TreeNode(1, l, r);

	cout << s.findBottomLeftValue(root);

	return 0;
}
