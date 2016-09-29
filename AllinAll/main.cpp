// Robin Andersson, ae5929, paul.robin.andersson@gmail.com
// 10340
#include <string>
#include <iostream>
#include <queue>

using namespace std;

int main()
{
	string first, second;
	while (!cin.eof())
	{
		queue<char> f;
		cin >> first >> second;

		for (int i = 0; i < first.length(); ++i)
			f.push(first[i]);

		for (int i = 0; i < second.length(); ++i)
		{
			if (f.size() != 0 && f.front() == second[i])
				f.pop();
		}

		cout << (f.empty() ? "Yes" : "No");
		if (!cin.eof())
			cout << endl;
	}

	return 0;
}