
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
    istringstream iss(s);

    string a, b, c, d, e;
    iss >> a >> b >> c >> d >> e;

    vector<string> results = { a, b, c, d, e };
    Print::Container(results);
    
    istringstream iss2(s);
    string temp;
    while (iss2 >> temp)
    {
        cout << temp << endl;
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