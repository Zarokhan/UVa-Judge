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

//#define DEBUG

using namespace std;

// Matrix
int* M[MCOLS];
vector<int> turns; // output path

int rows = 0;
int cols = 0;
const int getRows() { return rows; }

// Print method
void printcol(const int* col, const int lenght)
{
#ifdef DEBUG
	for (int i = 0; i < lenght; ++i)
		cout << col[i] << endl;
	cout << "-" << endl;
#endif
}

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

	printcol(column, rows);

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

void GoDownPath(const int column, const int index, int& total) // param 1: current column, param 2: index in column, param 3: total value
{
	int* col = new int[rows];
	vector<pair<int, int>> p; // possible, 1: index, 2: value

	memcpy(col, M[column], sizeof(int) * rows);
	printcol(col, rows);

	// left
	int valid = index - 1;
	if (valid < 0)
		valid = rows - 1;
	p.push_back(pair<int, int>(valid, col[valid]));

	// -> forward direction
	p.push_back(pair<int, int>(index, col[index]));

	// Right
	valid = index + 1;
	if (valid + 1 >= rows)
		valid = 0;
	p.push_back(pair<int, int>(valid, col[valid]));

#ifdef DEBUG
	for (int i = 0; i < 3; ++i)
		cout << p[i].second << endl;
	cout << "-" << endl;
#endif



	// Maybe need list to save two with same value
	int value = BIGNR;
	int in = 0;	// index
	for (int i = 0; i < 3; ++i)
	{
		if (p[i].second < value)
		{
			in = p[i].first;
			value = p[i].second;
		}
	}

	turns.push_back(in + 1);
	total += value;

	free(col);
	if (column < cols)
	{
		GoDownPath(column + 1, in, total);
	}
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
		while (true)//!startpoints.empty())
		{
			pair<int, int> p = startpoints.front();
			int total = p.first;
			int index = p.second;
			
			turns.push_back(index + 1);
			GoDownPath(1, index, total);

			// print 1: path
			for (auto it = turns.begin(); it != turns.end(); ++it)
				cout << *it << ' ';
			cout << endl;
			// print 2: total
			cout << total << endl;

			turns.clear();
			startpoints.pop();
			break;
		}
	}

	return 0;
}