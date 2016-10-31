// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 116 - Unidirectional TSP
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <array>

#define MCOLS 10
#define MROWS 100
#define BIGNR 1000000

//#define DEBUG

using namespace std;

struct Node
{
	Node(int value, pair<int,int> dim) : v(value), d(dim) { }
	Node() = default;
	int v = 0; // value
	pair<int, int> d; // dim
	bool discovered = false;

	vector<pair<int, int>> n; // neighbours
};

struct Path
{
	int v = 0; // value of path
	queue<int> p; // path
};

struct GNode
{

};

// Matrix
Node* M[MCOLS];
int rows = 0, cols = 0;

void DFS(const pair<int,int> v)
{
	stack<pair<int,int>> s;
	s.push(v);
	
	while (!s.empty())
	{
		Node& n = M[s.top().first][s.top().second];
		s.pop();

		if (!n.discovered)
		{
			n.discovered = true;
			pair<int, int> dim = pair<int,int>(n.d);

			if (dim.first < cols)
			{
				// Forward
				dim.first++;
				s.push(pair<int, int>(dim));
				n.n.push_back(pair<int, int>(dim));

				// left
				int valid = dim.second - 1;
				if (valid < 0)
					valid = rows - 1;

				s.push(pair<int, int>(dim.first, valid));
				n.n.push_back(pair<int, int>(dim.first, valid));

				// Right
				valid = dim.second + 1;
				if (valid + 1 >= rows)
					valid = 0;

				s.push(pair<int, int>(dim.first, valid));
				n.n.push_back(pair<int, int>(dim.first, valid));
			}
		}
	}
}

int main()
{
	// Initialize memory
	for (int i = 0; i < MCOLS; ++i)
	{
		M[i] = new Node[MROWS];
		for (int j = 0; j < MROWS; ++j)
			M[i][j] = Node();
	}

	while (!cin.eof())
	{
		// Input 
		cin >> rows >> cols;
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				int v;
				cin >> v;
				M[c][r] = Node(v, pair<int,int>(c, r));
			}
		}

		for (int i = 0; i < rows; ++i)
		{
			DFS(pair<int, int>(0, i));
		}
	}

	return 0;
}