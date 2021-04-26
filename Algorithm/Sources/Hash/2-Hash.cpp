#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

const int InValid = -1;
const int BucketSize = 26;

struct Value
{
    char alphabet;
    int cnt;
};

struct KeyValue
{
    KeyValue() :key(InValid), value() {}

    int key;
    Value value;
};

// overflow를 방지하기 위해 bucket_size로 모듈러 연산
int HashFunction(int key, int bucket_size)
{
    return key % bucket_size;
}

int main()
{
    string text = "aaabbbcccadd";
    KeyValue bucket[BucketSize] = {};

    for (int i = 0; i < text.size(); ++i)
    {
        char alphabet = text[i];
        int index = HashFunction((int)alphabet, BucketSize);

        bucket[index].key = (int)alphabet;
        bucket[index].value.alphabet = alphabet;
        bucket[index].value.cnt++;
    }

    // 출력
    for (int i = 0; i < BucketSize; ++i)
    {
        if (bucket[i].key == InValid)
        {
            continue;
        }

        cout << bucket[i].value.alphabet << " : " << bucket[i].value.cnt << endl;
    }

    return 0;
}
