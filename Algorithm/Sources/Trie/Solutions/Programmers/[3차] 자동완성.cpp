
// [3차] 자동완성
// https://programmers.co.kr/learn/courses/30/lessons/17685

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

    const TrieNode* Find(const string& text, int& outlevel) const
    {
        return Find(text.c_str(), text.size(), outlevel);
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

    const TrieNode* Find(const char* text, int size, int& outlevel) const
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

            if (cur->cnt == 1 && outlevel == 0)
            {
                outlevel = level;
            }
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



int solution(vector<string> words) 
{
    TrieNode trie;

    for (auto w : words)
    {
        trie.Insert(w);
    }

    int answer = 0;
    for (auto w : words)
    {
        int outlevel = 0;
        trie.Find(w, outlevel);

        if (outlevel == 0)
        {
            outlevel = w.size();
        }

        answer += outlevel;
    }

    return answer;
}

int main()
{
    //vector<string> words = { "go", "gone", "guild" };
    //vector<string> words = { "abc","def","ghi","jklm" };
    vector<string> words = { "word","war","warrior","world" };

    cout << solution(words);

    return 0;
}
