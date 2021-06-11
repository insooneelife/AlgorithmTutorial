
// Trie의 메모리 최적화

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

struct TrieNode
{
public:
    static TrieNode trie_pool[1000002];
    static int trie_idx;
    static const int Alphabets = 26;

    TrieNode() : has_value(false), cnt(0), childs()
    {}

    void Insert(const string& text)
    {
        Insert(text.c_str(), text.size());
    }

    const TrieNode* Find(const string& text) const
    {
        return Find(text.c_str(), text.size());
    }

private:

    void Insert(const char* text, int size)
    {
        TrieNode* cur = this;
        for (int i = 0; i < size; ++i)
        {
            int index = ToIndex(text[i]);
            if (cur->childs[index] == nullptr)
            {
                cur->childs[index] = Alloc();
            }

            cur = cur->childs[index];
            cur->cnt++;
        }
        cur->has_value = true;
    }

    const TrieNode* Find(const char* text, int size) const
    {
        const TrieNode* cur = this;
        int level = 0;

        for (int i = 0; i < size; ++i)
        {
            int index = ToIndex(text[i]);
            if (cur->childs[index] == nullptr)
            {
                return nullptr;
            }

            level++;
            cur = cur->childs[index];
        }

        return cur;
    }


    TrieNode* Alloc()
    {
        for (int i = 0; i < Alphabets; i++)
        {
            trie_pool[trie_idx].childs[i] = nullptr;
        }
        trie_pool[trie_idx].has_value = false;

        return &trie_pool[trie_idx++];
    }


    static int ToIndex(char alphabet)
    {
        return (int)(alphabet - 'a');
    }

    static char ToChar(int index)
    {
        return (char)index + 'a';
    }

public:
    TrieNode* childs[Alphabets];
    bool has_value;
    int cnt;
};

TrieNode TrieNode::trie_pool[1000002];
int TrieNode::trie_idx = 0;


