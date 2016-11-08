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
				x2 += t[i];
			else if (symb == '=')
				result += t[i];
			else
				x1 += t[i];
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

string NumToRoman(const int val)
{
	int rest = val;
	int ones = 0;
	int tens = 0;
	int hundreds = 0;
	int thousands = 0;

	if (rest >= 1000)
	{
		thousands = rest / 1000;
		rest = rest % 1000;
	}
	if (rest >= 100)
	{
		hundreds = rest / 100;
		rest = rest % 100;
	}
	if (rest >= 10)
	{
		tens = rest / 10;
		rest = rest % 10;
	}
	if (rest >= 1)
	{
		ones = rest / 1;
		rest = rest % 1;
	}
	
	string answer;
	for (int i = 0; i < thousands; ++i)
	{
		answer += "M";
	}
	for (int i = 0; i < hundreds; ++i)
	{
		answer += "C";
	}
	for (int i = 0; i < tens; ++i)
	{
		answer += "X";
	}
	for (int i = 0; i < ones; ++i)
	{
		answer += "I";
	}

	return answer;
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
		int first = RomanToNum(x1);
		int second = RomanToNum(x2);
		int res = RomanToNum(result);

		string str = NumToRoman(res);

		if (first + second == res)
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