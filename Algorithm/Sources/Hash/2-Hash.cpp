// 해시 테이블 관련 개념들의 탄생

// 'a'와 같은 알파벳들은 데이터 그 자체로서, 해시테이블에 저장될 값(Value)와 대응된다.
// 'a'의 아스키 값은 데이터의 고유한 식별값으로서, 키(Key)와 대응된다.
// 배열[26]은 해시 테이블의 저장공간으로서, 버킷(Bucket)과 대응된다.
// alphabet - 'a'라는 계산식은 각 데이터가 저장될 위치를 결정하는 방법으로서, 해시 함수(Hash Function)에 대응된다.
// hash function 통해 계산된 index는 실제 값이 bucket에 저장될 위치로서, 해시(Hashes)와 대응된다.



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


// 하지만 만약 대문자 알파벳이 요구사항에 추가된다면?