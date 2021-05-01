// 이진탐색트리 (Binary Search Tree)
// Binary Search Tree Template Implement (Key & Value & Compare & Iterate)

// 트리는 순회가 가능한 자료구조이다.
// 외부에서 for, while 루프와 같은 형태로 트리를 순회할 수 있어야한다.
// 또한 트리의 특정 구간을 표현하기 위한 수단도 필요하다.

// 이러한 작업이 가능하도록 하기 위해 반복자 패턴 (Iterator Pattern)을 이용한다.
// 순회가 가능한 모든 컨테이너는 자기자신의 순회방법을 정의한 반복자를 제공해야한다.
// 반복자를 통해 외부에서는 해당 컨테이너를 같은 인터페이스로 순회할 수 있고,
// 또 컨테이너의 특정 위치를 참조할 수 있다. (구간에 대한 표현도, [시작위치, 끝위치] 로 표현이 가능해진다.)

#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename KeyType, typename ValueType>
class TreeNode
{
public:
    TreeNode() :key(), value(), parent(nullptr), left(nullptr), right(nullptr) {}

    TreeNode(KeyType key, const ValueType& value, TreeNode<KeyType, ValueType>* const parent)
        : key(key), value(value), parent(parent), left(nullptr), right(nullptr) {}

    TreeNode(KeyType key, const ValueType& value, TreeNode<KeyType, ValueType>* const parent, TreeNode<KeyType, ValueType>* const left)
        : key(key), value(value), parent(parent), left(left), right(nullptr) {}

    TreeNode(
        KeyType key,
        const ValueType& value,
        TreeNode<KeyType, ValueType>* const parent,
        TreeNode<KeyType, ValueType>* const left,
        TreeNode<KeyType, ValueType>* const right)
        :
        key(key), value(value), parent(parent), left(left), right(right) {}

public:
    KeyType key;
    ValueType value;

private:
    template <typename T, typename U, typename V>
    friend class BinarySearchTree;

    template <typename T, typename U>
    friend TreeNode<T, U>* FindMin(TreeNode<T, U>* const);

    template<typename T, typename U>
    friend struct TreeIterator;

    TreeNode<KeyType, ValueType>* parent;
    TreeNode<KeyType, ValueType>* left;
    TreeNode<KeyType, ValueType>* right;
};

template <typename KeyType, typename ValueType>
static TreeNode<KeyType, ValueType>* FindMin(TreeNode<KeyType, ValueType>* const root)
{
    TreeNode<KeyType, ValueType>* min = root;
    while (min->left != nullptr)
    {
        min = min->left;
    }
    return min;
}

template<typename KeyType, typename ValueType, typename CompareType = less<KeyType>>
class BinarySearchTree
{
private:
    using NodeType = TreeNode<KeyType, ValueType>;

public:
    BinarySearchTree() : _root(nullptr) {}

    BinarySearchTree(NodeType* const root) : _root(root) {}

    BinarySearchTree(const BinarySearchTree& other)
    {
        cout << "copy construct BinarySearchTree" << endl;
        CopyTree(other._root, nullptr, _root);
    }

    ~BinarySearchTree()
    {
        cout << "destruct BinarySearchTree" << endl;
        DeleteTree(_root);
    }

    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
        cout << "copy assign BinarySearchTree" << endl;
        CopyTree(other._root, nullptr, _root);
        return *this;
    }

    NodeType* Search(KeyType key) const
    {
        return Search(key, _root);
    }

    void Insert(const KeyType& key, const ValueType& value)
    {
        if (_root == nullptr)
        {
            _head.left = _root;
            _head.right = _root;
            _root = new NodeType(key, value, &_head);
        }
        else
        {
            Insert(key, value, _root->parent, _root);
        }
    }

    void Delete(const KeyType& key)
    {
        Delete(key, _root);
    }

    void PrintAllTraverse() const
    {
        PrintAllTraverse(_root);
    }

    NodeType* FindMin()const
    {
        return ::FindMin<KeyType, ValueType>(_root);
    }

private:
    static NodeType* Search(KeyType key, NodeType* const root)
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

    // NodeType에 parent를 넘겨주기 위해 재귀 인자를 하나 더 사용
    static void Insert(const KeyType& key, const ValueType& value, NodeType* parent, NodeType*& root)
    {
        if (root == nullptr)
        {
            root = new NodeType(key, value, parent);
            //cout <<"key :" <<  root->key.key <<" parent : " << root->parent->key.key << endl;
        }

        else if (key == root->key)
            root->value = value;

        else if (CompareType()(key, root->key))
            Insert(key, value, root, root->left);

        else if (CompareType()(root->key, key))
            Insert(key, value, root, root->right);
    }


    static void Delete(const KeyType& key, NodeType*& root)
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
                NodeType* delete_node = root;
                root = root->right;
                delete delete_node;
            }

            // has left child
            else if (root->left != nullptr && root->right == nullptr)
            {
                NodeType* delete_node = root;
                root = root->left;
                delete delete_node;
            }
            // has two childs
            else
            {
                // find minimum node from right subtree
                NodeType* min = FindMin(root->right);

                // replace to min node key & value
                root->key = min->key;
                root->value = min->value;

                // delete
                Delete(min->key, root->right);
            }
        }
    }


    static void DeleteTree(NodeType* const root)
    {
        if (root == nullptr) return;

        // first delete both subtrees 
        DeleteTree(root->left);
        DeleteTree(root->right);

        cout << "delete : " << root->key.key << endl;

        delete root;
    }

    // NodeType에 parent를 넘겨주기 위해 재귀 인자를 하나 더 사용
    static NodeType* CopyTree(const NodeType* const root, NodeType* parent, NodeType*& copy)
    {
        if (root == nullptr)
            return nullptr;

        copy = new NodeType(root->key, root->value, parent, copy);
        copy->left = CopyTree(root->left, copy, copy->left);
        copy->right = CopyTree(root->right, copy, copy->right);
        return copy;
    }

    static void PreOrder(const NodeType* const root)
    {
        if (root == nullptr)
            return;

        cout << root->key.key << " ";
        PreOrder(root->left);
        PreOrder(root->right);
    }

    static void InOrder(const NodeType* const root)
    {
        if (root == nullptr)
            return;

        InOrder(root->left);
        cout << root->key.key << " ";
        InOrder(root->right);
    }

    static void PostOrder(const NodeType* const root)
    {
        if (root == nullptr)
            return;

        PostOrder(root->left);
        PostOrder(root->right);
        cout << root->key.key << " ";
    }

    static void PrintAllTraverse(const NodeType* const root)
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
    NodeType _head;
    NodeType* _root;
};


// 트리를 순회하기 위한 객체
template<typename KeyType, typename ValueType>
struct TreeIterator
{
    using NodeType = TreeNode<KeyType, ValueType>;

    TreeIterator() : _current(nullptr) {}
    TreeIterator(NodeType* tree_node) : _current(tree_node) {}

    // 루프 순회에 필요한 연산자들 정의
    TreeIterator& operator++() { return MoveNext(); }
    TreeIterator operator++(int) { return MoveNext(); }

    bool operator==(const TreeIterator& other) const { return _current == other._current; }
    bool operator!=(const TreeIterator& other) const { return !(*this == other); }

    NodeType* operator->() { return _current; }
    NodeType const* operator->() const { return _current; }

    NodeType& operator*() { return *_current; }
    NodeType operator*() const { return *_current; }

private:

    // 트리 노드를 중위순회로 한 칸 이동하는 함수
    TreeIterator& MoveNext()
    {
        // 오른쪽 서브트리가 존재하면?
        if (_current->right != nullptr)
        {
            // 오른쪽 서브트리의 최소노드로 이동 (가장 왼쪽 노드)
            _current = FindMin(_current->right);
            return *this;
        }

        while (true)
        {
            // 끝
            if (_current->parent == nullptr)
            {
                _current = nullptr;
                return *this;
            }

            // current가 이전 단계에서 루트의 왼쪽 서브트리였는지?
            if (_current->parent->left == _current)
            {
                _current = _current->parent;
                return *this;
            }

            _current = _current->parent;
        }
    }

private:
    NodeType* _current;
};

// 컨테이너의 시작에 대한 정의
template<typename KeyType, typename ValueType, typename CompareType>
TreeIterator<KeyType, ValueType> begin(const BinarySearchTree<KeyType, ValueType, CompareType>& tree)
{
    // begin은 현재 O(logN)
    // 최적화가 필요할듯?
    return TreeIterator<KeyType, ValueType>(tree.FindMin());
}

// 컨테이너의 끝에 대한 정의
template<typename KeyType, typename ValueType, typename CompareType>
TreeIterator<KeyType, ValueType> end(const BinarySearchTree<KeyType, ValueType, CompareType>& tree)
{
    return TreeIterator<KeyType, ValueType>(nullptr);
}

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
        return key > other.key;
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

using Tree = BinarySearchTree<Key, Value, less<Key>>;

// Tree 생성
Tree MakeTree()
{
    Tree tree;
    tree.Insert(Key(8), Value("root", 0));
    tree.Insert(Key(1), Value("a", 0));
    tree.Insert(Key(4), Value("b", 0));
    tree.Insert(Key(14), Value("c", 0));
    tree.Insert(Key(3), Value("d", 0));
    tree.Insert(Key(7), Value("e", 0));

    return tree;
}

int main()
{
    Tree tree = MakeTree();
    tree.PrintAllTraverse();

    // 이제 외부에서 for 루프를 이용한 순회가 가능하다
    for (TreeIterator<Key, Value> it = begin(tree); it != end(tree); it++)
    {
        cout << "it : " << it->key.key << endl;
        //cout << "it : " << (*it).key.key << endl;
    }


    return 0;
}
