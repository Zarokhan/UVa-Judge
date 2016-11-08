// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 185 Roman Numerals
#include <iostream>
#include <string>
#include <map>

using namespace std;

map<char, int> RN;
map<int, char> NR;

void GetInput(const string& input, string& x1, string& x2, string& result)
{
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
}

int RomanToNum(const string& val)
{
	int lenght = val.length();
	int sum = RN[val[0]];
	int before = RN[val[0]];

	for (int i = 1; i < lenght; ++i)
	{
		int v1 = RN[val[i]];

		if (before <= v1)
		{
			before = v1;
			sum += v1;
		}
		else
		{
			before = v1;
			sum -= v1;
		}
	}

	return sum;
}

int main()
{
	const int lenght = 7;
	const char Roman[lenght] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
	const int Num[lenght] = { 1, 5, 10, 50, 100, 500, 1000 };

	for (int i = 0; i < lenght; ++i)
	{
		RN[Roman[i]] = Num[i];
		NR[Num[i]] = Roman[i];
	}

	while (true)
	{
		string input;
		string x1, x2, result;
		getline(cin, input);
		
		if (input.c_str()[0] == '#')
			break;

		GetInput(input, x1, x2, result);
		int n1 = RomanToNum(x1);
		int n2 = RomanToNum(x2);
		int res = RomanToNum(result);

		if (n1 + n2 == res)
		{
			cout << "Correct" << endl;
		}
		else
		{
			cout << "incorrect" << endl;
		}

		int test = 0;
	}

	return 0;
}