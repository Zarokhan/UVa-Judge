// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 185 Roman Numerals
#include <iostream>
#include <string>

using namespace std;

int main()
{
	while (true)
	{
		string input;
		string x1, x2, result;
		getline(cin, input);
		
		if (input.c_str()[0] == '#')
			break;

		const char* t = input.c_str();
		int len = strlen(t);
		char symb = 't';
		for (int i = 0; i < len; ++i)
		{
			if (t[i] == '+' || t[i] == '=')
			{
				symb = t[i];
			}
			else
			{
				if (symb == '+')
				{
					x2 += t[i];
				}
				else if (symb == '=')
				{
					result += t[i];
				}
				else
				{
					x1 += t[i];
				}
			}
		}

		int test = 0;
	}

	return 0;
}