// 이진탐색트리 (Binary Search Tree)

#include <iostream>
#include <vector>
using namespace std;


class TreeNode
{
public:
    TreeNode(int key, int value) : key(key), value(value), left(nullptr), right(nullptr) {}
    TreeNode(int key, int value, TreeNode* left) : key(key), value(value), left(left), right(nullptr) {}
    TreeNode(int key, int value, TreeNode* left, TreeNode* right) : key(key), value(value), left(left), right(right) {}

public:
    int key;
    int value;

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

    // 복사 생성자는 CopyTree를 이용하여 Preorder로 트리를 복사함
    BinarySearchTree(const BinarySearchTree& other)
    {
        cout << "copy construct BinarySearchTree" << endl;
        CopyTree(other._root, _root);
    }

    // 소멸자는 DeleteTree를 이용하여 Postorder로 트리를 파괴함
    ~BinarySearchTree()
    {
        cout << "destruct BinarySearchTree" << endl;
        DeleteTree(_root);
    }

    // 대입 연산자는 CopyTree를 이용하여 Preorder로 트리를 복사함
    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
        cout << "copy assign BinarySearchTree" << endl;
        CopyTree(other._root, _root);
        return *this;
    }


    // 외부에 필요한 인자만 열어 두고, 내부적으로 재귀함수를 호출하도록 함.
    // 재귀함수에 들어갈 TreeNode root는 내부에서 넘겨줌.
    // root를 건드리지 않는 함수는 const 처리하여, 디버깅 스코프를 줄인다.
    TreeNode* Search(int key) const
    {
        return Search(key, _root);
    }

    void Insert(int key, int value)
    {
        Insert(key, value, _root);
    }

    void Delete(int key)
    {
        Delete(key, _root);
    }

    void PrintAllTraverse() const
    {
        PrintAllTraverse(_root);
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

    static void Insert(int key, int value, TreeNode*& root)
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


    static TreeNode* FindMin(TreeNode* root)
    {
        while (root->left != nullptr)
        {
            root = root->left;
        }
        return root;
    }

    static void Delete(int key, TreeNode*& root)
    {
        // search
        // key not found
        if (root == nullptr)
        {
        }
        else if (key < root->key)
        {
            Delete(key, root->left);
        }
        else if (key > root->key)
        {
            Delete(key, root->right);
        }
        // key found
        else
        {
            // has no child
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                root = nullptr;
            }

            // has right child
            else if (root->left == nullptr && root->right != nullptr)
            {
                TreeNode* delete_node = root;
                root = root->right;
                delete delete_node;
            }

            // has left child
            else if (root->left != nullptr && root->right == nullptr)
            {
                TreeNode* delete_node = root;
                root = root->left;
                delete delete_node;
            }
            // has two childs
            else
            {
                // find minimum node from right subtree
                TreeNode* min = FindMin(root->right);

                // replace to min node key & value
                root->key = min->key;
                root->value = min->value;

                // delete
                Delete(min->key, root->right);
            }
        }
    }


    static void DeleteTree(TreeNode* root)
    {
        if (root == nullptr) return;

        // first delete both subtrees 
        DeleteTree(root->left);
        DeleteTree(root->right);

        cout << "delete : " << root->key << endl;

        delete root;
    }

    static TreeNode* CopyTree(TreeNode* root, TreeNode*& copy)
    {
        if (root == nullptr)
            return nullptr;

        copy = new TreeNode(root->key, root->value);
        copy->left = CopyTree(root->left, copy->left);
        copy->right = CopyTree(root->right, copy->right);
        return copy;
    }

    static void PreOrder(TreeNode* root)
    {
        if (root == nullptr)
            return;

        cout << root->key << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }

    static void InOrder(TreeNode* root)
    {
        if (root == nullptr)
            return;

        InOrder(root->left);
        cout << root->key << " ";
        InOrder(root->right);
    }

    static void PostOrder(TreeNode* root)
    {
        if (root == nullptr)
            return;

        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->key << " ";
    }

    static void PrintAllTraverse(TreeNode* root)
    {
        cout << "PreOrder" << endl;
        PreOrder(root);
        cout << endl << "InOrder" << endl;
        InOrder(root);
        cout << endl << "PostOrder" << endl;
        PostOrder(root);
        cout << endl;
    }

private:
    TreeNode* _root;
};

// Tree 생성
BinarySearchTree MakeTree()
{
    TreeNode* left_subtree = new TreeNode(3, 33, new TreeNode(1, 11), new TreeNode(6, 66, new TreeNode(4, 44), new TreeNode(7, 77)));
    TreeNode* right_subtree = new TreeNode(10, 1010, nullptr, new TreeNode(14, 1414, new TreeNode(13, 1313)));
    TreeNode* root = new TreeNode(8, 88, left_subtree, right_subtree);

    BinarySearchTree tree(root);

    return tree;
}

int main()
{
    BinarySearchTree tree = MakeTree();

    tree.PrintAllTraverse();

    // search
    TreeNode* node = tree.Search(7);
    cout << endl << "Search  key : " << node->key << " value : " << node->value << endl;

    // insert
    cout << endl << "Insert key : 5  value : 55" << endl;
    tree.Insert(5, 55);

    tree.PrintAllTraverse();

    BinarySearchTree tree2 = tree;

    cout << "copy" << endl;
    tree2.PrintAllTraverse();

    cout << endl << "Delete key : 5, key : 8" << endl;
    tree.Delete(5);
    tree.Delete(8);

    tree.PrintAllTraverse();

    return 0;
}

