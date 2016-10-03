// Robin Andersson, ae5929, paul.robin.andersson@gmail.com
// 374
// http://stackoverflow.com/questions/13553057/using-powx-y-in-large-numbers
// https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/modular-exponentiation
#include <iostream>

using namespace std;

int B = 0;
int P = 0;
int M = 0;

int mymod(int B, int P, int M)
{
	// If something is power of 0 it's 1
	if (P == 0)
		return 1;

	// If P is not an even number
	if (P % 2 != 0)
	{
		return (B % M * mymod(B, P - 1, M)) % M;
	}
	else
	{
		// if P is even we can safley divide by 2
		int j = mymod(B, P / 2, M);
		return ((j % M) * (j % M)) % M;
	}
}

int main()
{
	while (cin >> B >> P >> M)
	{
		float result = mymod(B, P, M);
		cout << result << endl;
	}

	return 0;
}