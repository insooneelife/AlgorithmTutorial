// hanbin8269 의 작업공간
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    string text = "aaabbbccc";
    unordered_map<char, int> um;
    for (int i = 0; i < text.size(); i++) {
        um[text.at(i)] += 1;
    }
    for (auto elem : um) {
        cout << "key : " << elem.first << " value : " << elem.second << endl;
    }
}