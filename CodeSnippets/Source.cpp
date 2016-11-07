#include <iostream>

#define MAX 101
#define INFINITY 9999999

int map[MAX][MAX];
int weight[MAX][MAX];
int path[MAX][MAX];

int sizeX, sizeY;

using namespace std;

int min(int x, int y)
{
	bool isTop = false;
	bool isButtom = false;
	int checkAbove = y + 1;
	if (checkAbove == sizeY)
	{
		checkAbove = 0;
		isButtom = true;
	}

	int checkUnder = y - 1;
	if (checkUnder == -1)
	{
		checkUnder = sizeY - 1;
		isTop = true;
	}

	int above = weight[x + 1][checkAbove];
	int mid = weight[x + 1][y];
	int under = weight[x + 1][checkUnder];

	//Could be done better below!
	//Order to always pick 0 if possible.
	if (isTop)
	{
		if (mid <= above && mid <= under)
		{
			path[x][y] = 0;
			return mid;
		}

		if (above <= mid && above <= under)
		{
			path[x][y] = 1;
			return above;
		}

		if (under <= mid && under <= above)
		{
			path[x][y] = -1;
			return under;
		}
	}
	else if (isButtom)
	{
		if (above <= mid && above <= under)
		{
			path[x][y] = 1;
			return above;
		}

		if (under <= mid && under <= above)
		{
			path[x][y] = -1;
			return under;
		}

		if (mid <= above && mid <= under)
		{
			path[x][y] = 0;
			return mid;
		}
	}
	else
	{
		if (under <= mid && under <= above)
		{
			path[x][y] = -1;
			return under;
		}

		if (mid <= above && mid <= under)
		{
			path[x][y] = 0;
			return mid;
		}

		if (above <= mid && above <= under)
		{
			path[x][y] = 1;
			return above;
		}
	}

}


int main()
{
	while (cin >> sizeY >> sizeX)
	{
		//load map
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
				cin >> map[x][y];
		}

		//load firstrow
		int minY = 0;
		int minYValue = INFINITY;
		for (int y = 0; y < sizeY; y++)
		{
			weight[sizeX - 1][y] = map[sizeX - 1][y];
			if (sizeX == 1)
			{
				if (weight[sizeX - 1][y] < minYValue)
				{
					minYValue = weight[sizeX - 1][y];
					minY = y;							//Start at lowest amount.
				}
			}
		}

		//Loop the rest.
		for (int x = sizeX - 2; x >= 0; x--)
		{
			for (int y = 0; y < sizeY; y++)
			{
				weight[x][y] = min(x, y) + map[x][y];
				if (x == 0)
				{
					if (weight[x][y] < minYValue)
					{
						minYValue = weight[x][y];
						minY = y;
					}
				}
			}
		}


		//Print path
		int nextY = minY;
		for (int x = 0; x < sizeX; x++)
		{
			cout << nextY + 1;
			if (x <= sizeX - 2)
				cout << " ";
			nextY += path[x][nextY];
			if (nextY == -1)
				nextY = sizeY - 1;
			if (nextY == sizeY)
				nextY = 0;

		}
		cout << endl << weight[0][minY] << endl;
	}
}