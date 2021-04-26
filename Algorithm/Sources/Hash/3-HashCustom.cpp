// 해시 테이블 만들어보기

// void Add(int key, Value value)
// key가 이미 있으면 value를 갱신
// key가 없으면 value를 추가

// bool GetValue(int key, Value& value)
// key가 있으면 value를 매개변수를 통해 참조함, return true
// key가 없으면 return false

// void Print()
// 모든 데이터 출력





#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

const int InValid = -1;
const int BucketSize = 26;

struct Value
{
    Value() : alphabet(0), cnt(0) {}
    Value(char alphabet, int cnt) : alphabet(alphabet), cnt(cnt) {}

    char alphabet;
    int cnt;
};

struct KeyValue
{
    KeyValue() : key(InValid), value() {}
    KeyValue(int key, Value value) : key(key), value(value) {}

    int key;
    Value value;
};



class HashTable
{
public:
    HashTable(int bucket_size) : _bucket_size(bucket_size), _bucket(bucket_size) {}

    // key가 이미 있으면 value를 갱신
    // key가 없으면 value를 추가
    void Add(int key, Value value)
    {
        int index = HashFunction(key, _bucket_size);
        list<KeyValue>& chain_list = _bucket[index];

        // chaining 된 데이터들 중 key를 찾음
        auto it = find_if(begin(chain_list), end(chain_list), [key](const KeyValue& a)
            {
                return a.key == key;
            });

        if (it != end(chain_list))
        {
            it->value = value;
        }
        else
        {
            chain_list.push_back(KeyValue(key, value));
        }
    }

    // value를 read
    bool GetValue(int key, Value& value) const
    {
        int index = HashFunction(key, _bucket_size);
        const list<KeyValue>& chain_list = _bucket[index];

        auto it = find_if(begin(chain_list), end(chain_list), [key](const KeyValue& a)
            {
                return a.key == key;
            });

        if (it != end(chain_list))
        {
            value = it->value;
            return true;
        }
        return false;
    }

    void Print() const
    {
        for (const list<KeyValue>& chain_list : _bucket)
        {
            for (const KeyValue& key_value : chain_list)
            {
                cout << key_value.key << "\t" << key_value.value.alphabet << "\t" << key_value.value.cnt << endl;
            }
        }
    }

private:
    // overflow를 방지하기 위해 bucket_size로 모듈러 연산
    int HashFunction(int key, int bucket_size) const
    {
        return key % bucket_size;
    }

private:
    int _bucket_size;
    vector<list<KeyValue>> _bucket;
};

int main()
{

    string text = "aaabbbcccdddeeefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    HashTable hash(26);

    for (auto c : text)
    {
        Value value;
        if (hash.GetValue(c, value))
        {
            value.cnt++;
            hash.Add(c, value);
        }
        else
        {
            value.alphabet = c;
            value.cnt = 1;
            hash.Add(c, value);
        }
    }

    hash.Print();


    return 0;
}
