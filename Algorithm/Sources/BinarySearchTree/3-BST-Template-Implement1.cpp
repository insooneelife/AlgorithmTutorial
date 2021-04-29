// 이진탐색트리 (Binary Search Tree)
// Binary Search Tree Template Implement (Value)

// 트리에 저장되는 데이터는 int 타입에 한정되어서는 안된다.
// template을 이용하여 모든 타입을 저장할 수 있는 트리를 설계한다.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename ValueType>
class TreeNode
{
public:
    TreeNode(int key, const ValueType& value)
        : key(key), value(value), left(nullptr), right(nullptr) {}

    TreeNode(int key, const ValueType& value, TreeNode<ValueType>* const left)
        : key(key), value(value), left(left), right(nullptr) {}

    TreeNode(int key, const ValueType& value, TreeNode<ValueType>* const left, TreeNode<ValueType>* const right)
        : key(key), value(value), left(left), right(right) {}

public:
    int key;
    ValueType value;

private:
    template <typename T>
    friend class BinarySearchTree;

    TreeNode<ValueType>* left;
    TreeNode<ValueType>* right;
};

template<typename ValueType>
class BinarySearchTree
{
public:
    BinarySearchTree(TreeNode<ValueType>* const root) : _root(root) {}

    BinarySearchTree(const BinarySearchTree& other)
    {
        cout << "copy construct BinarySearchTree" << endl;
        CopyTree(other._root, _root);
    }

    ~BinarySearchTree() 
    {
        cout << "destruct BinarySearchTree" << endl;
        DeleteTree(_root); 
    }

    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
        cout << "copy assign BinarySearchTree" << endl;
        CopyTree(other._root, _root);
        return *this;
    }

    TreeNode<ValueType>* Search(int key) const
    {
        return Search(key, _root);
    }

    void Insert(int key, const ValueType& value)
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
    static TreeNode<ValueType>* Search(int key, TreeNode<ValueType>* const root)
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

    static void Insert(int key, const ValueType& value, TreeNode<ValueType>*& root)
    {
        if (root == nullptr)
            root = new TreeNode<ValueType>(key, value);

        else if (key == root->key)
            root->value = value;

        else if (key < root->key)
            Insert(key, value, root->left);

        else if (key > root->key)
            Insert(key, value, root->right);
    }


    static TreeNode<ValueType>* FindMin(TreeNode<ValueType>* const root)
    {
        TreeNode<ValueType>* min = root;
        while (min->left != nullptr)
        {
            min = min->left;
        }
        return min;
    }

    static void Delete(int key, TreeNode<ValueType>*& root)
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
                TreeNode<ValueType>* delete_node = root;
                root = root->right;
                delete delete_node;
            }

            // has left child
            else if (root->left != nullptr && root->right == nullptr)
            {
                TreeNode<ValueType>* delete_node = root;
                root = root->left;
                delete delete_node;
            }
            // has two childs
            else
            {
                // find minimum node from right subtree
                TreeNode<ValueType>* min = FindMin(root->right);

                // replace to min node key & value
                root->key = min->key;
                root->value = min->value;

                // delete
                Delete(min->key, root->right);
            }
        }
    }


    static void DeleteTree(TreeNode<ValueType>* const root)
    {
        if (root == nullptr) return;

        // first delete both subtrees 
        DeleteTree(root->left);
        DeleteTree(root->right);

        cout << "delete : " << root->key << endl;

        delete root;
    }

    static TreeNode<ValueType>* CopyTree(const TreeNode<ValueType>* const root, TreeNode<ValueType>*& copy)
    {
        if (root == nullptr)
            return nullptr;

        copy = new TreeNode<ValueType>(root->key, root->value);
        copy->left = CopyTree(root->left, copy->left);
        copy->right = CopyTree(root->right, copy->right);
        return copy;
    }

    static void PreOrder(const TreeNode<ValueType>* const root)
    {
        if (root == nullptr)
            return;

        cout << root->key << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }

    static void InOrder(const TreeNode<ValueType>* const root)
    {
        if (root == nullptr)
            return;

        InOrder(root->left);
        cout << root->key << " ";
        InOrder(root->right);
    }

    static void PostOrder(const TreeNode<ValueType>* const root)
    {
        if (root == nullptr)
            return;

        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->key << " ";
    }

    static void PrintAllTraverse(const TreeNode<ValueType>* const root)
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
    TreeNode<ValueType>* _root;
};

struct Value
{
    Value() : value(0) {}
    Value(string name, int value) : name(name), value(value) {}

public:
    string name;
    int value;
};


// Tree 생성
BinarySearchTree<Value> MakeTree()
{
    TreeNode<Value>* left_subtree = 
        new TreeNode<Value>(3, Value("a", 33),
            new TreeNode<Value>(1, Value("b", 11)),
            new TreeNode<Value>(6, Value("c", 66), 
                new TreeNode<Value>(4, Value("d", 44)), 
                new TreeNode<Value>(7, Value("e", 77))));
    
    TreeNode<Value>* right_subtree = 
        new TreeNode<Value>(10, Value("f", 1010),
            nullptr, 
            new TreeNode<Value>(14, Value("g", 1414), new TreeNode<Value>(13, Value("h", 1313))));

    TreeNode<Value>* root = new TreeNode<Value>(8, Value("root", 88), left_subtree, right_subtree);

    BinarySearchTree<Value> tree(root);
    return tree;
}


int main()
{
    BinarySearchTree<Value> tree = MakeTree();

    tree.PrintAllTraverse();

    // search
    TreeNode<Value>* node = tree.Search(7);
    cout << endl << "Search  key : " << node->key << " value name : " << node->value.name << "  value : " << node->value.value << endl;

    // insert
    cout << endl << "Insert key : 5  value : 55" << endl;
    tree.Insert(5, Value("z", 55));

    tree.PrintAllTraverse();

    BinarySearchTree<Value> tree2 = tree;

    cout << "copy" << endl;
    tree2.PrintAllTraverse();

    cout << endl << "Delete key : 5, key : 8" << endl;
    tree.Delete(5);
    tree.Delete(8);

    tree.PrintAllTraverse();

    return 0;
}
