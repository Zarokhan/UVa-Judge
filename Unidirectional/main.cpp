// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 116 - Unidirectional TSP
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <array>
#define MCOLS 10
#define MROWS 100
#define BIGNR 1000000

using namespace std;

// Matrix
int* M[MCOLS];
int rows = 0;
const int getRows() { return rows; }
int cols = 0;

// Pick smallest element in array
// c param: index for column
queue<pair<int, int>> picksmallest(const int rows, const int cols, const int c)
{
	// smallest
	int* column = new int[rows];

	queue<pair<int, int>> good; // pair<value, index>
	int value = BIGNR;
	int index = 0;
	good.push(pair<int, int>(value, index));

	memcpy(column, M[c], sizeof(int) * rows);

	//for (int i = 0; i < rows; ++i)
	//	cout << column[i] << endl;
	
	// Find valid solution
	for (int i = 0; i < rows; ++i)
	{
		if (column[i] < good.front().first)
		{
			// Clear
			queue<pair<int, int>> empty;
			swap(good, empty);
			// Push
			good.push(pair<int, int>(column[i], i));
		}
		else if (column[i] == good.front().first)
		{
			// Push
			good.push(pair<int, int>(column[i], i));
		}
	}

	
	//sort(column, column + rows);


	free(column);
	return good;
}

void GoDownPath(const int column, const int index, int total) // param 1: current column, param 2: index in column, param 3: total value
{
	int* test = new int[rows];

	memcpy(test, M[column], sizeof(int) * rows);
}

int main()
{
	// Initialize memory
	for (int i = 0; i < MCOLS; ++i)
	{
		M[i] = new int[MROWS];
		for (int j = 0; j < MROWS; ++j)
			M[i][j] = 0;
	}

	while (!cin.eof())
	{
		// Input 
		cin >> rows >> cols;
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				cin >> M[c][r];
			}
		}

		queue<pair<int, int>> startpoints = picksmallest(rows, cols, 0); // pair: value, index
		// pick the 3 next valid tiles in next column
		while (!startpoints.empty())
		{
			pair<int, int> p = startpoints.front();
			int value = p.first;
			int index = p.second;

			GoDownPath(0, index, value);

			startpoints.pop();
		}
	}

	return 0;
}