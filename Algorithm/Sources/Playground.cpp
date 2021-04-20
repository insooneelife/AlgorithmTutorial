
#include "Library/STL.h"
#include "Library/Utility.h"

#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;



int main() 
{

    string s = "split\ton   \t white\nspace   .";
    vector<string> results;
    istringstream iss(s);
    for (string s; iss >> s;)
    {
        results.push_back(s);
    }

    cout << s << endl;
    for (auto e : results)
    {
        cout << e << "\n";
    }

    return 0;
}

/*
split   on       whitespace   .

split
on
whitespace
.
*/