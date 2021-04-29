// 이진탐색트리 (Binary Search Tree)
// Binary Search Tree Template Implement (Key & Value & Compare)

// 트리의 비교방법은 반드시 오름차순이 아닐수도 있다.
// 트리의 비교방법 자체를 Compare라는 템플릿 인자로 받아서, less, greater 모두에 대해 열려있도록 설계한다.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename KeyType, typename ValueType>
class TreeNode
{
public:
    TreeNode(KeyType key, const ValueType& value)
        : key(key), value(value), left(nullptr), right(nullptr) {}

    TreeNode(KeyType key, const ValueType& value, TreeNode<KeyType, ValueType>* const left)
        : key(key), value(value), left(left), right(nullptr) {}

    TreeNode(KeyType key, const ValueType& value, TreeNode<KeyType, ValueType>* const left, TreeNode<KeyType, ValueType>* const right)
        : key(key), value(value), left(left), right(right) {}

public:
    KeyType key;
    ValueType value;

private:
    template <typename T, typename U, typename V>
    friend class BinarySearchTree;

    TreeNode<KeyType, ValueType>* left;
    TreeNode<KeyType, ValueType>* right;
};


template<typename KeyType, typename ValueType, typename CompareType = less<KeyType>>
class BinarySearchTree
{
public:
    BinarySearchTree() : _root(nullptr) {}

    BinarySearchTree(TreeNode<KeyType, ValueType>* const root) : _root(root) {}

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

    TreeNode<KeyType, ValueType>* Search(KeyType key) const
    {
        return Search(key, _root);
    }

    void Insert(const KeyType& key, const ValueType& value)
    {
        Insert(key, value, _root);
    }

    void Delete(const KeyType& key)
    {
        Delete(key, _root);
    }

    void PrintAllTraverse() const
    {
        PrintAllTraverse(_root);
    }

private:
    static TreeNode<KeyType, ValueType>* Search(KeyType key, TreeNode<KeyType, ValueType>* const root)
    {
        // 기저 조건
        if (root == nullptr)
            return nullptr;

        if (key == root->key)
            return root;

        // 함수객체를 활용하여, 일반화된 비교연산을 이용함
        if (CompareType()(key, root->key))
            return Search(key, root->left);

        if (CompareType()(root->key, key))
            return Search(key, root->right);
    }

    static void Insert(const KeyType& key, const ValueType& value, TreeNode<KeyType, ValueType>*& root)
    {
        if (root == nullptr)
            root = new TreeNode<KeyType, ValueType>(key, value);

        else if (key == root->key)
            root->value = value;

        else if (CompareType()(key, root->key))
            Insert(key, value, root->left);

        else if (CompareType()(root->key, key))
            Insert(key, value, root->right);
    }


    static TreeNode<KeyType, ValueType>* FindMin(TreeNode<KeyType, ValueType>* const root)
    {
        TreeNode<KeyType, ValueType>* min = root;
        while (min->left != nullptr)
        {
            min = min->left;
        }
        return min;
    }

    static void Delete(const KeyType& key, TreeNode<KeyType, ValueType>*& root)
    {
        // search
        // key not found
        if (root == nullptr)
        {
        }
        else if (CompareType()(key, root->key))
        {
            Delete(key, root->left);
        }
        else if (CompareType()(root->key, key))
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
                TreeNode<KeyType, ValueType>* delete_node = root;
                root = root->right;
                delete delete_node;
            }

            // has left child
            else if (root->left != nullptr && root->right == nullptr)
            {
                TreeNode<KeyType, ValueType>* delete_node = root;
                root = root->left;
                delete delete_node;
            }
            // has two childs
            else
            {
                // find minimum node from right subtree
                TreeNode<KeyType, ValueType>* min = FindMin(root->right);

                // replace to min node key & value
                root->key = min->key;
                root->value = min->value;

                // delete
                Delete(min->key, root->right);
            }
        }
    }


    static void DeleteTree(TreeNode<KeyType, ValueType>* const root)
    {
        if (root == nullptr) return;

        // first delete both subtrees 
        DeleteTree(root->left);
        DeleteTree(root->right);

        cout << "delete : " << root->key.key << endl;

        delete root;
    }

    static TreeNode<KeyType, ValueType>* CopyTree(const TreeNode<KeyType, ValueType>* const root, TreeNode<KeyType, ValueType>*& copy)
    {
        if (root == nullptr)
            return nullptr;

        copy = new TreeNode<KeyType, ValueType>(root->key, root->value);
        copy->left = CopyTree(root->left, copy->left);
        copy->right = CopyTree(root->right, copy->right);
        return copy;
    }

    static void PreOrder(const TreeNode<KeyType, ValueType>* const root)
    {
        if (root == nullptr)
            return;

        cout << root->key.key << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }

    static void InOrder(const TreeNode<KeyType, ValueType>* const root)
    {
        if (root == nullptr)
            return;

        InOrder(root->left);
        cout << root->key.key << " ";
        InOrder(root->right);
    }

    static void PostOrder(const TreeNode<KeyType, ValueType>* const root)
    {
        if (root == nullptr)
            return;

        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->key.key << " ";
    }

    static void PrintAllTraverse(const TreeNode<KeyType, ValueType>* const root)
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
    TreeNode<KeyType, ValueType>* _root;
};

struct Key
{
    Key() : key(0) {}
    Key(int key) : key(key) {}

public:
    bool operator<(const Key& other) const
    {
        return key < other.key;
    }

    bool operator>(const Key& other) const
    {
        return key < other.key;
    }

    bool operator==(const Key& other) const
    {
        return key == other.key;
    }

public:
    int key;
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
//BinarySearchTree<Key, Value> MakeTree()
BinarySearchTree<Key, Value, greater<Key>> MakeTree()
{
    //BinarySearchTree<Key, Value> tree;
    BinarySearchTree<Key, Value, greater<Key>> tree;

    tree.Insert(Key(8), Value("root", 0));

    tree.Insert(Key(1), Value("a", 0));
    tree.Insert(Key(4), Value("b", 0));
    tree.Insert(Key(14), Value("c", 0));
    tree.Insert(Key(3), Value("d", 0));

    return tree;
}

int main()
{
    //BinarySearchTree<Key, Value> tree = MakeTree();
    BinarySearchTree<Key, Value, greater<Key>> tree = MakeTree();

    tree.PrintAllTraverse();

    // search
    TreeNode<Key, Value>* node = tree.Search(Key(7));
    cout << endl << "Search  key : " << node->key.key << " value name : " << node->value.name << "  value : " << node->value.value << endl;

    // insert
    cout << endl << "Insert key : 5  value : 55" << endl;
    tree.Insert(Key(5), Value("z", 55));

    tree.PrintAllTraverse();

    //BinarySearchTree<Key, Value> tree2 = tree;
    BinarySearchTree<Key, Value, greater<Key>> tree2 = tree;

    cout << "copy" << endl;
    tree2.PrintAllTraverse();

    cout << endl << "Delete key : 5, key : 8" << endl;
    tree.Delete(Key(5));
    tree.Delete(Key(8));

    tree.PrintAllTraverse();

    return 0;
}
