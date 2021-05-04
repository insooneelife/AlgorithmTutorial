#include <iostream>
#include <vector>

//#include "Print.h"

using namespace std;

const int Alphabets = 26;

struct TrieNode
{
public:
    TrieNode() : has_value(false), childs()
    {}

    ~TrieNode()
    {
        for (int i = 0; i < Alphabets; ++i)
        {
            if (childs[i] != nullptr)
            {
                delete childs[i];
            }
        }
    }

    void Insert(const char* text)
    {
        // null 문자
        if (*text == 0)
        {
            has_value = true;
        }
        else
        {
            int index = ToIndex(*text);
            if (childs[index] == nullptr)
            {
                childs[index] = new TrieNode();
            }
            childs[index]->Insert(text + 1);
        }
    }

    const TrieNode* Find(const char* text) const
    {
        if (*text == 0)
        {
            return this;
        }

        int index = ToIndex(*text);
        if (childs[index] == nullptr)
        {
            return nullptr;
        }
        childs[index]->Find(text + 1);
    }

    void FindBySuffixWildcard(const string& prefix, int wildcard_size, vector<string>& finds) const
    {
        const TrieNode* node = Find(prefix.c_str());

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

        // print suffix
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

enum class WildcardType
{
    Prefix, Suffix
};

WildcardType GetWildcardData(const string& keyword, string& substr, int& wildcard_size)
{
    const char kWildcard = '?';

    WildcardType type = WildcardType::Prefix;

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
        trie.Insert(w.c_str());
    }

    vector<string> finds;
    for (auto k : queries)
    {
        string substr;
        int wildcard_size = 0;
        WildcardType type = GetWildcardData(k, substr, wildcard_size);

        if (type == WildcardType::Prefix)
        {
            trie.FindByPrefixWildcard(substr, wildcard_size, finds);
        }
        else
        {
            trie.FindBySuffixWildcard(substr, wildcard_size, finds);
        }
        answer.push_back(finds.size());

        //Print::Container(finds);
        //cout << k << "   type : " << (int)type << "  sub : " << substr << "  size : " << wildcard_size << endl << endl;;
        finds.clear();
    }

    return answer;
}

int main()
{
    vector<string> words = { "frodo", "front", "frost", "frozen", "frame", "kakao", "aaaaot" };
    vector<string> queries = { "fro??", "????o", "fr???", "fro???", "pro?" };

    // 동적할당으로 구현한 Trie는 100만짜리 테스트에서 문제가 생김
    // 또한 스택 오버플로우 문제도 생김
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

    //Print::Container(answer);




    return 0;
}