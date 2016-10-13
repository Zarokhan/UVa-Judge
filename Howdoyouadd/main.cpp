// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 10943
#include <iostream>
#define KMAX 110

using namespace std;

int K_TABLE[KMAX][KMAX];

int myfunc(int N, int K)
{
	if (N < 0 || K < 0)
		return 0;
	if (K_TABLE[N][K] != -1)
		return K_TABLE[N][K];
	
	long long sum = 0;
	for (int i = 0; i < N + 1; i++)
	{
		sum += myfunc(N - i, K - 1) % 1000000;
	}
	K_TABLE[N][K] = sum % 1000000;
	int test = 0;
	return K_TABLE[N][K];
}

void resetTable()
{
	for (int i = 0; i < KMAX; i++)
	{
		for (int j = 0; j < KMAX; j++)
		{
			K_TABLE[i][j] = -1;
		}
	}
}

int main()
{
	int N = 20, K = 2;

	while (true) {
		cin >> N >> K;

		if (N == 0 && K == 0)
			return 0;

		resetTable();
		K_TABLE[0][0] = 1;
		cout << myfunc(N, K) << endl;
		int test = 0;
	}

	return 0;
}