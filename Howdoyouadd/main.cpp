// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 10943
// https://f0rth3r3c0rd.wordpress.com/2011/09/05/uva-10943-how-do-you-add/
#include <iostream>
#define KMAX 100
#define DEBUG_

using namespace std;

int K_TABLE[KMAX][KMAX];

int myfunc(int N, int K)
{
	// Base cases
	//else if (K == 2)
	//	return (N + 1) % 1000000;
	if (K_TABLE[N][K] != -1)	// No need for recalculation
		return K_TABLE[N][K];
	
	long long sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += myfunc(N - i, K - 1) % 1000000;
	}
	K_TABLE[N][K] = sum % 1000000;
	return K_TABLE[N][K];
}

void resetTable()
{
	for (int i = 0; i < KMAX; i++)
	{
		for (int j = 0; j < KMAX; j++)
		{
#ifdef DEBUG_
			if (i == 0)
				K_TABLE[i][j] = j;
			else if (j == 0)
				K_TABLE[i][j] = i;
			else
#endif
			K_TABLE[i][j] = -1;
		}
	}
}

int main()
{
	int N = 20, K = 2;

	while (N != 0 && K != 0) {
		cin >> N >> K;
		resetTable();
		K_TABLE[0][0] = 1;
		cout << myfunc(N, K) << endl;
		int test = 0;
	}

	return 0;
}