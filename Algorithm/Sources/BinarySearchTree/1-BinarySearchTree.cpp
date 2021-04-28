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
    TreeNode* left;
    TreeNode* right;
};

// Tree 생성
TreeNode* MakeTree()
{
    TreeNode* left_subtree = new TreeNode(3, 33, new TreeNode(1, 11), new TreeNode(6, 66, new TreeNode(4, 44), new TreeNode(7, 77)));
    TreeNode* right_subtree = new TreeNode(10, 1010, nullptr, new TreeNode(14, 1414, new TreeNode(13, 1313)));
    TreeNode* tree = new TreeNode(8, 88, left_subtree, right_subtree);

    return tree;
}

TreeNode* Search(int key, TreeNode* root)
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

// 참조자를 이용한 방법
void Insert(int key, int value, TreeNode*& root)
{
    // root는 TreeNode 포인터의 참조자이기 때문에,
    // root가 nullptr인 시점에 그 nullptr을 담고있는 변수 자체일 것이다. (즉, 이 root의 parent의 left나 right 중 하나일 것이다.)
    // 포인터의 참조로 root를 가져왔기 때문에, root = new TreeNode(key, value)를 통해, 해당 변수가 직접 새 노드를 참조할 수 있을 것이다.
    if (root == nullptr)
        root = new TreeNode(key, value);

    else if (key == root->key)
        root->value = value;

    else if (key < root->key)
        Insert(key, value, root->left);

    else if (key > root->key)
        Insert(key, value, root->right);
}

// 반환을 이용한 방법
TreeNode* Insert2(int key, int value, TreeNode* root)
{
    // 삽입되는 경우에만 새로 생성된 노드를 반환하여, root->left나 root->right가 새 노드를 참조하도록 한다.
    if (root == nullptr)
        return new TreeNode(key, value);

    else if (key == root->key)
        root->value = value;

    // root->left는 왼쪽 서브트리의 루트를 참조하도록 한다.
    // 물론 이미 참조하고 있지만, 새 노드가 삽입되는 상황에 대한 예외 반환을 가능하도록 하기 위함이다.
    else if (key < root->key)
        root->left = Insert2(key, value, root->left);

    // left와 마찬가지
    else if (key > root->key)
        root->right = Insert2(key, value, root->right);

    // 특별한 일이 없다면 자기자신을 반환하여, root->left나 root->right의 참조가 변하지 않도록 한다.
    return root;
}


// 1. 자식이 없는 node 제거 - 그냥 제거
// 2. 한 개의 자식을 갖는 node 제거 - 제거 후 자식으로 대체
// 3. 두 개의 자식을 갖는 node 제거
// (left subtree의 최소 node) or (right subtree의 최대 node)를 고른다. (이 예제는 left subtree의 최소노드로 작성)
// left subtree의 최소 node를 찾는다.
// 제거될 node를 최소 node로 대체한다.
// 하위 서브트리에서 최소 node를 제거한다.

TreeNode* FindMin(TreeNode* root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

void Delete(int key, TreeNode*& root)
{
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
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
        }

        else if (root->left == nullptr && root->right != nullptr)
        {
            TreeNode* delete_node = root;
            root = root->right;
            delete delete_node;
        }

        else if (root->left != nullptr && root->right == nullptr)
        {
            TreeNode* delete_node = root;
            root = root->left;
            delete delete_node;
        }
        else
        {
            TreeNode* min = FindMin(root->right);

            // replace to min node key & value
            root->key = min->key;
            root->value = min->value;

            Delete(min->key, root->right);
        }
    }
}

void PreOrder(TreeNode* root)
{
    if (root == nullptr)
        return;

    cout << root->key << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

void InOrder(TreeNode* root)
{
    if (root == nullptr)
        return;

    InOrder(root->left);

    cout << root->key << " ";

    InOrder(root->right);
}

void PostOrder(TreeNode* root)
{
    if (root == nullptr)
        return;

    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->key << " ";
}

void DeleteTree(TreeNode* root)
{
    if (root == nullptr) return;

    // first delete both subtrees 
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}

void PrintAllTraverse(TreeNode* root)
{
    cout << "PreOrder" << endl;
    PreOrder(root);
    cout << endl << "InOrder" << endl;
    InOrder(root);
    cout << endl << "PostOrder" << endl;
    PostOrder(root);
    cout << endl;
}

int main()
{
    TreeNode* tree = MakeTree();

    PrintAllTraverse(tree);

    // search
    TreeNode* node = Search(7, tree);
    cout << endl << "Search  key : " << node->key << " value : " << node->value << endl;

    // insert
    cout << endl << "Insert key : 5  value : 55" << endl;
    Insert2(5, 55, tree);

    PrintAllTraverse(tree);


    cout << endl << "Delete key : 5, key : 8" << endl;
    Delete(5, tree);
    Delete(8, tree);

    PrintAllTraverse(tree);

    DeleteTree(tree);

    PrintAllTraverse(tree);


    return 0;
}
