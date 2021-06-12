
// 가사 검색
// https://programmers.co.kr/learn/courses/30/lessons/60060

// 문제풀이
// 1. 문자열 trie와 역방향 문자열 trie를 만든다.
// 2. 각 trie에 insert 하는 과정에서, 그 경로에 있는 노드들에 현재까지 거쳐간 문자열들의 길이를 카운팅하는 맵을 만든다.
// 3. Suffix가 ?인 query가 들어오면 일반 trie에서 prefix를 탐색하고, 마지막 노드에서 카운팅맵을 통해 (?길이 + Prefix길이)인 문자열의 개수 반환
// 4. Prefix가 ?인 query가 들어오면 역방향 trie에서 prefix를 탐색하고, 마지막 노드에서 카운팅맵을 통해 (?길이 + Prefix길이)인 문자열의 개수 반환


// 시행착오
// 2. 재귀함수로 인한 스택오버플로우 이슈
// 3. ????? 예외처리
// 4. 재귀함수로 인한 시간초과 이슈라기보다는 그냥 카운트맵을 미리 만들었어야 했음
// 5. 인덱스 범위초과 (segmentation fault), trie, rtrie를 만들었기 때문에 trie_pool 사이즈도 2배로 해야 함 
// 6. ????? 예외처리가 시간초과가 되는 케이스, 모든 query가 ????.. 로만 이루어진 경우
// 7. 이 문제는 Trie 동적할당을 수행하여도 문제 없음




#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_map>

//#include "Print.h"
using namespace std;

const int Alphabets = 26;


struct TrieNode
{
public:
    static vector<TrieNode> trie_pool;
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

            cur->childs[index]->size_count[size]++;
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

    int FindBySuffixWildcard(const string& prefix, int wildcard_size) const
    {
        const TrieNode* node = Find(prefix.c_str(), prefix.size());

        if (node != nullptr)
        {
            auto it = node->size_count.find(prefix.size() + wildcard_size);
            if (it != end(node->size_count))
            {
                return it->second;
            }
        }
        return 0;
    }

private:
    static TrieNode* Alloc()
    {
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
    unordered_map<int, int> size_count;
};

vector<TrieNode> TrieNode::trie_pool(2000004);
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
    TrieNode rtrie;
    unordered_map<int, int> size_count;

    for (auto w : words)
    {
        trie.Insert(w.c_str(), w.size());

        reverse(begin(w), end(w));
        rtrie.Insert(w.c_str(), w.size());

        size_count[w.size()]++;
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
            auto it = size_count.find(wildcard_size);
            if (it != end(size_count))
            {
                cnt = it->second;
            }
            
            answer.push_back(cnt);
        }
        else if (type == WildcardType::Prefix)
        {
            reverse(begin(substr), end(substr));

            int cnt = rtrie.FindBySuffixWildcard(substr, wildcard_size);
            answer.push_back(cnt);
        }
        else
        {
            int cnt = trie.FindBySuffixWildcard(substr, wildcard_size);
            answer.push_back(cnt);
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
    
    vector<int> answer = solution(words, queries);
    //Print::Container(answer);

    return 0;
}