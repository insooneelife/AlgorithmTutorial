
// 길 찾기 게임
// https://programmers.co.kr/learn/courses/30/lessons/42892

// 시행착오
// 1. 삽입순서를 만들기 위한 정렬 정책을 잘 생각해야한다.

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include "Print.h"

using namespace std;

struct Value
{
    int x;
    int y;
    int index;
};

class TreeNode
{
public:
    TreeNode(int key, Value value) : key(key), value(value), left(nullptr), right(nullptr) {}
    TreeNode(int key, Value value, TreeNode* left) : key(key), value(value), left(left), right(nullptr) {}
    TreeNode(int key, Value value, TreeNode* left, TreeNode* right) : key(key), value(value), left(left), right(right) {}

    ~TreeNode()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }

public:
    int key;
    Value value;

private:
    // left, right는 BinarySearchTree에서만 접근 가능하도록 한다.
    friend class BinarySearchTree;

    TreeNode* left;
    TreeNode* right;
};

// TreeNode들의 집합을 관리하는 객체
class BinarySearchTree
{
public:
    BinarySearchTree(TreeNode* root) : _root(root) {}

    ~BinarySearchTree()
    {
        if (_root != nullptr)
            delete _root;
    }

    TreeNode* Search(int key) const
    {
        return Search(key, _root);
    }

    void Insert(int key, Value value)
    {
        Insert(key, value, _root);
    }

    void PreOrder(vector<int>& buffer) const
    {
        PreOrder(_root, buffer);
    }

    void PostOrder(vector<int>& buffer) const
    {
        PostOrder(_root, buffer);
    }


private:
    // 재귀함수들은 이 객체 외부에서는 사용될 일이 없으므로, private으로 캡슐화 함
    // 또한, 내부 변수를 건드릴 일도 없으므로, static으로 정의함

    static TreeNode* Search(int key, TreeNode* root)
    {
        // 기저 조건
        if (root == nullptr)
            return nullptr;

        if (key == root->key)
            return root;

        if (key < root->key)
            return Search(key, root->left);

        if (key > root->key)
            return Search(key, root->right);
    }

    static void Insert(int key, Value value, TreeNode*& root)
    {
        if (root == nullptr)
            root = new TreeNode(key, value);

        else if (key == root->key)
            root->value = value;

        else if (key < root->key)
            Insert(key, value, root->left);

        else if (key > root->key)
            Insert(key, value, root->right);
    }


    static void PreOrder(TreeNode* root, vector<int>& buffer)
    {
        if (root == nullptr)
            return;

        buffer.push_back(root->value.index);
        PreOrder(root->left, buffer);
        PreOrder(root->right, buffer);
    }

    static void InOrder(TreeNode* root)
    {
        if (root == nullptr)
            return;

        InOrder(root->left);
        cout << root->key << " " << root->value.index << endl;
        InOrder(root->right);
    }

    static void PostOrder(TreeNode* root, vector<int>& buffer)
    {
        if (root == nullptr)
            return;

        PostOrder(root->left, buffer);
        PostOrder(root->right, buffer);
        buffer.push_back(root->value.index);
    }


private:
    TreeNode* _root;
};

vector<vector<int>> solution(vector<vector<int>> nodeinfo) 
{
    BinarySearchTree tree(nullptr);

    vector<Value> nodes;

    for (int i = 0; i < nodeinfo.size(); ++i)
    {
        Value value;
        value.index = i + 1;
        value.x = nodeinfo[i][0];
        value.y = nodeinfo[i][1];
        nodes.push_back(value);
    }

    sort(begin(nodes), end(nodes), [](Value a, Value b)
        {
            if (a.y == b.y)
            {
                return a.x < b.x;
            }

            return a.y > b.y; 
        });

    for (int i = 0; i < nodes.size(); ++i)
    {
        tree.Insert(nodes[i].x, nodes[i]);
    }

    vector<int> preorder;
    tree.PreOrder(preorder);

    vector<int> postorder;
    tree.PostOrder(postorder);

    vector<vector<int>> answer = { preorder, postorder };
    return answer;
}


int main()
{
    vector<vector<int>> nodeinfo = { {5, 3} ,{11, 5},{13, 3},{3, 5},{6, 1},{1, 3},{8, 6},{7, 2},{2, 2} };

    vector<vector<int>> answer = solution(nodeinfo);
    
    Print::ContainerInContainer(answer);


    return 0;
}