
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

struct Data
{
	int maxh;
	int maxd;

	Data(int maxh, int maxd) : maxh(maxh), maxd(maxd){}

};

class Solution 
{
public:
	Data calc(TreeNode* root)
	{
		Data now(0, 0);
		Data l(0, 0);
		Data r(0, 0);

		if (root->left != nullptr)
		{
			l = calc(root->left);
			l.maxh += 1;
		}

		if(root->right != nullptr)
		{
			r = calc(root->right);
			r.maxh += 1;
		}

		now.maxh = max(l.maxh, r.maxh);
		now.maxd = max(l.maxd, r.maxd);
		now.maxd = max(now.maxd, r.maxh + l.maxh);

		return now;
	}

	int diameterOfBinaryTree(TreeNode* root) 
	{
		Data d = calc(root);

		//cout << d.maxh << " " << d.maxd;
		return d.maxd;
	}
};


int main()
{
	Solution s;

	TreeNode* ll = new TreeNode(4);
	TreeNode* lr = new TreeNode(5);
	TreeNode* l = new TreeNode(2, ll, lr);
	TreeNode* r = new TreeNode(3);
	TreeNode* root = new TreeNode(1, l, r);

	s.diameterOfBinaryTree(root);

	return 0;
}
