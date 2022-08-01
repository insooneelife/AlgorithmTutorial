#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MIN = std::numeric_limits<int>::min();
typedef long long ll;

class Solution
{
public:
	vector<vector<ll>> cache;
	ll maxval;
	ll maxfrom;
	ll maxto;

	void init(const string& s)
	{
		maxval = 1;
		maxfrom = 0;
		maxto = 0;

		cache.resize(s.size() + 1);
		for (int i = 0; i < cache.size(); ++i)
			cache[i].resize(s.size() + 1);

		for (int i = 0; i < cache.size(); ++i)
		{
			for (int j = 0; j < cache[i].size(); ++j)
			{
				if (i == j)
				{
					cache[i][j] = 1;
				}
				else
				{
					cache[i][j] = 0;
				}
			}
		}
	}

	ll palindrom_array(const string& s)
	{
		ll i = 0;
		ll j = 1;
		ll line = 0;
		while (!(i == 0 && j == s.size()))
		{
			for (i = 0; i < s.size() - line; i++, j++)
			{
				ll strsize = (ll)(j - i + 1);
				ll ret;

				if (s[j] == s[i])
				{
					ret = cache[i + 1][j - 1];
					if (ret == strsize - 2)
					{
						cache[i][j] = ret + 2;
						maxval = cache[i][j];
						maxfrom = i;
						maxto = j;
						continue;
					}
				}

				ll left = cache[i][j - 1];
				ll right = cache[i + 1][j];

				cache[i][j] = max(left, right);
			}

			line++;
			i = 0;
			j = line;
		}

		return cache[0][s.size() - 1];
	}

	string longestPalindrome(string s)
	{
		init(s);

		ll ans = palindrom_array(s);

		return s.substr(maxfrom, maxto - maxfrom + 1);
	}

	void print()
	{
		for (int i = 0; i < cache.size() - 1; ++i)
		{
			for (int j = 0; j < cache[i].size() - 1; ++j)
			{
				cout << cache[i][j] << ", ";
			}
			cout << endl;
		}
		cout << endl;
	}
};