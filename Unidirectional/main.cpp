// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 116 - Unidirectional TSP
#include <iostream>
#include <vector>

#define ROWS 11
#define COLS 101
#define BIGNR 99999999

using namespace std;

struct Node
{
	Node(int value) : val(value), orginal(value) { }
	Node() = default;
	
	int val = 0;					
	int parent = 0;
	int orginal = 0;
};

Node* M[ROWS];				// Matrix
int rows = 0, cols = 0;		// Dimensions

void reset()
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			M[i][j].val = 0;
			M[i][j].parent = 0;
			M[i][j].orginal = 0;
		}
	}
}

int main()
{
	for (int i = 0; i < ROWS; ++i)
	{
		M[i] = new Node[COLS];
	}

	while (!cin.eof())
	{
		reset();

		// Input 
		cin >> rows >> cols;
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				int v;
				cin >> v;
				M[i][j] = Node(v);
			}
		}

		// Render maze
		//for (int i = 0; i < rows; ++i)
		//{
		//	for (int j = 0; j < cols; ++j)
		//	{
		//		cout << M[i][j].val;
		//	}
		//	cout << endl;
		//}

		// Calc parent & sum
		int test = 0;
		for (int j = cols - 2; j >= 0; --j)
		{
			for (int i = 0; i < rows; ++i)
			{
				int val = M[i][j].val;
				int parent = (rows + i - 1) % rows;

				// First child
				M[i][j].val = val + M[parent][j + 1].val;
				M[i][j].parent = parent;

				// Second
				int sum = val + M[i][j + 1].val;
				if (sum < M[i][j].val)
				{
					M[i][j].val = sum;
					M[i][j].parent = i;
				}
				else if (sum == M[i][j].val && M[i][j].parent > i)
				{
					M[i][j].parent = i;
				}

				// Third
				parent = (rows + i + 1) % rows;
				sum = val + M[parent][j + 1].val;
				if (sum < M[i][j].val)
				{
					M[i][j].val = sum;
					M[i][j].parent = parent;
				}
				else if (sum == M[i][j].val && M[i][j].parent > parent)
				{
					M[i][j].parent = parent;
				}
			}
		}

		int lowest = BIGNR;
		int lowest_row = 0;

		for (int i = 0; i < rows; ++i)
		{
			if (M[i][0].val < lowest)
			{
				lowest = M[i][0].val;
				lowest_row = i;
			}
		}

		vector<int> path;

		for (int i = 0; i < cols; ++i)
		{
			path.push_back(lowest_row + 1);
			lowest_row = M[lowest_row][i].parent;
		}

		int si = path.size();
		for (int i = 0; i < si; ++i)
		{
			cout << path[i];
			if (i < si - 1)
				cout << " ";
		}
		cout << endl << lowest << endl;
	}

	// Delete on heap
	for (int i = 0; i < ROWS; ++i)
		delete[] M[i];

	return 0;
}