// 암호 만들기 (백트래킹)
// https://www.acmicpc.net/problem/1759

#include<vector>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool check(int n, string s) 
{
    int ja = 0;
    int mo = 0;

    for (int i = 0; i < n; i++) 
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') 
        {
            mo++;
        }
        else 
        {
            ja++; 
        }
    }

    return mo >= 1 && ja >= 2;

}

void Go(int n, vector<char>& alpha, string password, int i) 
{
    if (n == password.length()) 
    {
        //cout << "p: " << password << endl;
        if (check(n, password)) 
        {
            cout << password << '\n';
        }
        return;
    }

    if (i >= alpha.size())
        return;

    Go(n, alpha, password + alpha[i], i + 1);
    Go(n, alpha, password, i + 1);
}


int main() 
{
    int l, c;
    cin >> l >> c;

    vector<char> al;

    for (int i = 0; i < c; i++) 
    {
        char k;
        cin >> k;
        al.push_back(k);
    }

    sort(al.begin(), al.end());
    Go(l, al, "", 0);

    return 0;

}