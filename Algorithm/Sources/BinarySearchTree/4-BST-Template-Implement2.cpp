// 이진탐색트리 (Binary Search Tree)
// Binary Search Tree Template Implement (Key & Value)

// 탐색트리의 Key도 반드시 int 타입이 아닐 수 있다.
// Key도 모든 타입에 대해 동작하도록 구현해보자.
// 단, Key의 경우 트리 내부 알고리즘에서 Compare(<, >) 연산자와 Equal(==) 연산자를 사용하기 때문에,
// 객체 내부에서 연산자 오버리딩을 해주어야 한다.

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
    template <typename T, typename U>
    friend class BinarySearchTree;

    TreeNode<KeyType, ValueType>* left;
    TreeNode<KeyType, ValueType>* right;
};

template<typename KeyType, typename ValueType>
class BinarySearchTree
{
public:
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

    void Insert(KeyType key, const ValueType& value)
    {
        Insert(key, value, _root);
    }

    void Delete(KeyType key)
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

        if (key < root->key)
            return Search(key, root->left);

        if (key > root->key)
            return Search(key, root->right);
    }

    static void Insert(KeyType key, const ValueType& value, TreeNode<KeyType, ValueType>*& root)
    {
        if (root == nullptr)
            root = new TreeNode<KeyType, ValueType>(key, value);

        else if (key == root->key)
            root->value = value;

        else if (key < root->key)
            Insert(key, value, root->left);

        else if (key > root->key)
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

    static void Delete(KeyType key, TreeNode<KeyType, ValueType>*& root)
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
    // 트리에서 비교에 필요한 연산자들을 정의해둔다.
    bool operator<(const Key& other)
    {
        return key < other.key;
    }

    bool operator>(const Key& other)
    {
        return key > other.key;
    }

    bool operator==(const Key& other)
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
BinarySearchTree<Key, Value> MakeTree()
{
    TreeNode<Key, Value>* left_subtree =
        new TreeNode<Key, Value>(Key(3), Value("a", 33),
            new TreeNode<Key, Value>(Key(1), Value("b", 11)),
            new TreeNode<Key, Value>(Key(6), Value("c", 66),
                new TreeNode<Key, Value>(Key(4), Value("d", 44)),
                new TreeNode<Key, Value>(Key(7), Value("e", 77))));

    TreeNode<Key, Value>* right_subtree =
        new TreeNode<Key, Value>(Key(10), Value("f", 1010),
            nullptr,
            new TreeNode<Key, Value>(Key(14), Value("g", 1414), new TreeNode<Key, Value>(Key(13), Value("h", 1313))));

    TreeNode<Key, Value>* root = new TreeNode<Key, Value>(Key(8), Value("root", 88), left_subtree, right_subtree);

    BinarySearchTree<Key, Value> tree(root);
    return tree;
}


int main()
{
    BinarySearchTree<Key, Value> tree = MakeTree();

    tree.PrintAllTraverse();

    // search
    TreeNode<Key, Value>* node = tree.Search(Key(7));
    cout << endl << "Search  key : " << node->key.key << " value name : " << node->value.name << "  value : " << node->value.value << endl;

    // insert
    cout << endl << "Insert key : 5  value : 55" << endl;
    tree.Insert(Key(5), Value("z", 55));

    tree.PrintAllTraverse();

    BinarySearchTree<Key, Value> tree2 = tree;

    cout << "copy" << endl;
    tree2.PrintAllTraverse();

    cout << endl << "Delete key : 5, key : 8" << endl;
    tree.Delete(Key(5));
    tree.Delete(Key(8));

    tree.PrintAllTraverse();

    return 0;
}
