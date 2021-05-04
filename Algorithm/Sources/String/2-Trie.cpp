
// 시행착오
// 1. 동적할당에 대한 메모리 초과 이슈
// 2. 재귀함수로 인한 스택오버플로우 이슈
// 3. ????? 예외처리
// 4. 재귀함수로 인한 시간초과 이슈?




#include <iostream>
#include <vector>
#include <stack>

#include "Print.h"
using namespace std;

const int Alphabets = 26;

struct TrieNode
{
public:
    static TrieNode trie_pool[1000002];
    static int trie_idx;

    TrieNode() : has_value(false), childs()
    {}

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
        }
        cur->has_value = true;
    }

    const TrieNode* Find(const char* text, int size) const
    {
        const TrieNode* cur = this;

        for (int i = 0; i < size; ++i)
        {
            int index = ToIndex(text[i]);
            if (cur->childs[index] == nullptr)
            {
                return nullptr;
            }

            cur = cur->childs[index];
        }

        return cur;
    }

    void FindBySuffixWildcard(const string& prefix, int wildcard_size, vector<string>& finds) const
    {
        const TrieNode* node = Find(prefix.c_str(), prefix.size());

        if (node == nullptr)
        {
            // no prefix
        }
        else
        {
            string temp = prefix;
            node->FindBySuffixWildcardImpl(temp, wildcard_size, finds);
        }
    }

    void FindByPrefixWildcard(const string& suffix, int wildcard_size, vector<string>& finds) const
    {
        string buffer = "";
        FindByPrefixWildcardImpl(suffix.c_str(), wildcard_size, buffer, finds);
    }

private:
    void FindBySuffixWildcardImpl(string& buffer, int wildcard_size, vector<string>& finds) const
    {
        if (wildcard_size < 0)
        {
            return;
        }

        if (has_value && wildcard_size == 0)
        {
            finds.push_back(buffer);
            return;
        }

        for (int i = 0; i < Alphabets; ++i)
        {
            if (childs[i] != nullptr)
            {
                buffer.push_back(ToChar(i));
                childs[i]->FindBySuffixWildcardImpl(buffer, wildcard_size - 1, finds);
                buffer.pop_back();
            }
        }
    }

    void FindByPrefixWildcardImpl(const char* suffix, int wildcard_size, string& buffer, vector<string>& finds) const
    {
        if (*suffix == 0)
        {
            if (has_value)
            {
                finds.push_back(buffer);
            }
            return;
        }

        for (int i = 0; i < Alphabets; ++i)
        {
            char alphabet = ToChar(i);
            if (childs[i] != nullptr)
            {
                if (wildcard_size <= 0)
                {
                    if (*suffix == alphabet)
                    {
                        buffer.push_back(alphabet);
                        childs[i]->FindByPrefixWildcardImpl(suffix + 1, wildcard_size - 1, buffer, finds);
                        buffer.pop_back();
                    }
                }
                else
                {
                    buffer.push_back(alphabet);
                    childs[i]->FindByPrefixWildcardImpl(suffix, wildcard_size - 1, buffer, finds);
                    buffer.pop_back();
                }
            }
        }
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
};

TrieNode TrieNode::trie_pool[1000002];
int TrieNode::trie_idx = 0;

enum class WildcardType
{
    Prefix, Suffix
};

WildcardType GetWildcardData(const string& keyword, string& substr, int& wildcard_size)
{
    const char kWildcard = '?';

    WildcardType type = WildcardType::Prefix;
    wildcard_size = keyword.size();

    for (int i = 0; i < keyword.size() - 1; ++i)
    {
        int ni = i + 1;
        char current = keyword[i];
        char next = keyword[ni];

        // suffix wildcard
        if (current != kWildcard && next == kWildcard)
        {
            type = WildcardType::Suffix;

            substr = keyword.substr(0, ni);
            wildcard_size = keyword.size() - ni;
            break;
        }

        // prefix wildcard
        if (current == kWildcard && next != kWildcard)
        {
            type = WildcardType::Prefix;

            substr = keyword.substr(ni, keyword.size() - ni);
            wildcard_size = ni;
            break;
        }
    }

    return type;
}

vector<int> solution(vector<string> words, vector<string> queries)
{
    vector<int> answer;
    TrieNode trie;

    for (auto w : words)
    {
        trie.Insert(w.c_str(), w.size());
    }
        
    vector<string> finds;
    for (auto q : queries)
    {
        string substr;
        int wildcard_size = 0;
        WildcardType type = GetWildcardData(q, substr, wildcard_size);

        if (substr.size() == 0)
        {
            int cnt = 0;
            for (auto w : words)
            {
                if (w.size() == wildcard_size)
                {
                    cnt++;
                }
            }

            answer.push_back(cnt);
        }
        else if (type == WildcardType::Prefix)
        {
            trie.FindByPrefixWildcard(substr, wildcard_size, finds);
            answer.push_back(finds.size());
        }
        else
        {
            trie.FindBySuffixWildcard(substr, wildcard_size, finds);
            answer.push_back(finds.size());
        }

        //Print::Container(finds);
        //cout << q << "   type : " << (int)type << "  sub : " << substr << "  size : " << wildcard_size << endl << endl;;
        finds.clear();
    }
    
    return answer;
}

int main()
{
    vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao", "aaaaot" };
    vector<string> queries = { "fro??", "????o", "fr???", "fro???", "pro?", "?????" };

    /*
    string testword = "";
    for (int i = 0; i < 1000000; ++i)
    {
        testword += 'a';
    }
    words.push_back(testword);

    string testquery = "??";
    for (int i = 0; i < 1000000 - 2; ++i)
    {
        testquery += 'a';
    }
    queries.push_back(testquery);
    */


    vector<int> answer = solution(words, queries);

    Print::Container(answer);




    return 0;
}