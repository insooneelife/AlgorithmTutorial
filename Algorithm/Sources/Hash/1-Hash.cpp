// 해시 예제 1.
// a-z 까지의 알파벳으로 이루어진 문자열이 들어올 때, 각 알파벳들의 개수를 카운팅하는 알고리즘 구현



#include <string>
#include <iostream>

using namespace std;

int main()
{
    string text = "aaabbbcccadd";
    int cnt[26] = {};

    for (int i = 0; i < text.size(); ++i)
    {
        char alphabet = text[i];

        // 저장될 위치
        int index = alphabet - 'a';
        cnt[index] ++;
    }

    // 출력
    for (int i = 0; i < 26; ++i)
    {
        char alphabet = i + 'a';
        cout << alphabet << " : " << cnt[i] << endl;
    }

    return 0;
}