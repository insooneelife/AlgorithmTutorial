// 해시 테이블(Hash Table)

// 해시 테이블이란?
// key와 value 형태로 자료를 저장하는 자료구조
// key는 유일성을 갖는 숫자로, 해시맵 인덱싱을 위해 사용된다.
// value는 실제 데이터가 저장되는 변수이다.
// key를 통해 빠르게 원하는 value를 참조해올 수 있다.


// 해시 예제 1.
// vector<int> inputs = { 50, 51, 51, 52, 51, 52, 51, 55, 54, 53, 52, 58, 59, 57 };
// 각 원소 K의 범위 (50 <= K < 60)
// 다음과 같은 인풋이 들어온다고 가정했을 때 각 원소의 개수를 카운팅하는 알고리즘을 작성.


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

void HashExample()
{
    vector<int> inputs = { 50, 51, 51, 52, 51, 52, 51, 55, 54, 53, 52, 58, 59, 57 };

    int bucket[10] = {};

    for(int i = 0; i<inputs.size(); ++i)
}


int main()
{
    
    

    return 0;
}


// 해시 예제1
// 완주하지 못한 선수
// https://programmers.co.kr/learn/courses/30/lessons/42576

// 해시 예제2
// 위장
// https://programmers.co.kr/learn/courses/30/lessons/42578