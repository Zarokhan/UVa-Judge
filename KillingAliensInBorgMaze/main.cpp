// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 10307
#include "myman.h"

int main(int args, char* arg[])
{
	int test_cases;
	cin >> test_cases;

	int y;				// Rows of input
	int x;				// Number of characters in each row
	string input;		// Line input
	char c;				// Character in line
	int n = 0;			// Index for iterator

	// For each test case
	for (int j = 0; j < test_cases; ++j)
	{
		ResetNodes();
		cin >> x >> y;
		for (int k = 0; k < y+1; ++k) 
		{
			// Get maze input
			getline(cin, input);
			for (string::iterator it = input.begin(); it != input.end(); ++it)
			{
				c = *it;
				nodes[k-1][n].c = c;
				++n;
			}
			n = 0;
		}
		// Calculate shortest distance
		InitializeNodes(y, x);
		CalculateWeights();

		// Clear aliens
		while (!m_alien.empty())
			m_alien.pop();

	}

	return 0;
}

void ResetNodes()
{
	for (int i = 0; i < MAZE_SIZE; ++i)
	{
		for (int j = 0; j < MAZE_SIZE; ++j)
		{
			nodes[i][j] = Node();
		}
	}

	important.clear();
	edges.clear();
	while (!m_alien.empty())
		m_alien.pop();
}

void InitializeNodes(const int ySize, const int xSize)
{
	// Calculate adjacency matrix
	for (int y2 = 0; y2 < ySize; ++y2)
	{
		for (int x2 = 0; x2 < xSize; ++x2)
		{
			nodes[y2][x2].pos = pair<int, int>(y2, x2);

			switch (nodes[y2][x2].c)
			{
			case ' ':
				nodes[y2][x2].type = 1;
				break;
			case 'A':
				nodes[y2][x2].type = 2;
				m_alien.push(pair<int, int>(y2, x2));
				important.push_back(&nodes[y2][x2]);
				break;
			case 'S':
				nodes[y2][x2].type = 3;
				m_start.first = y2;
				m_start.second = x2;
				important.push_back(&nodes[y2][x2]);
				break;
			}
		}
	}

}

void CalculateWeights()
{
	for (int i = 0; i < important.size(); ++i)
	{
		Node* in = important[i];
		BreadthFirstSearch(in->pos);	//	VERY IMPORTANT THIS STAYS IN THE FIRST LOOP
										//	IF IN SECOND LOOP, GG LIFE INTEL PENTIUM
		for (int j = 0; j < important.size(); ++j)
		{
			Node* jn = important[j];
			if (in == jn)
				continue;

			//Edge e;
			int weight = 0;
			GoDownPath(in->pos, jn->pos, weight);
			//e.connection = pair<int, int>(i, j);
		}
	}

}

void GoDownPath(const pair<int, int>& closed, pair<int, int>& open, int & weight)
{
	if (closed == open)
		return;

	++weight;
	pair<int, int> p = nodes[open.first][open.second].parent;
	GoDownPath(closed, p, weight);
}

void BreadthFirstSearch(pair<int, int> start)
{
	bool m_processed[MAZE_SIZE][MAZE_SIZE];
	bool m_discovered[MAZE_SIZE][MAZE_SIZE];

	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			m_processed[i][j] = false;
			m_discovered[i][j] = false;
		}
	}

	queue<pair<int, int>> q;	// Queue of vertices to visit
	pair<int, int> v;				// Current vertex

									// Enqueue first vertex
	q.push(start);
	m_discovered[start.first][start.second] = true;

	while (!q.empty())
	{
		// Dequeue
		v.first = q.front().first;
		v.second = q.front().second;
		q.pop();

		// Process vertex
		process_vertex(v);
		m_processed[v.first][v.second] = true;

		// Discover nearby edges
		for (int i = 0; i < 4; ++i)
		{
			// Addition to v index (south, west, east & north)
			pair<int, int> a(0, 0);
			switch (i)
			{
			case 0:
				a.first = 1;
				break;
			case 1:
				a.second = -1;
				break;
			case 2:
				a.second = 1;
				break;
			case 3:
				a.first = -1;
				break;
			}
			// Check if valid edge
			if (valid_edge(v, a))
			{
				pair<int, int> vi(v.first + a.first, v.second + a.second);	// valid index
				// Check if it's discovered
				if (!m_discovered[vi.first][vi.second]) {
					// Enqueue valid undiscovered vertex
					q.push(pair<int, int>(vi.first, vi.second));
					m_discovered[vi.first][vi.second] = true;
					nodes[vi.first][vi.second].parent = pair<int, int>(v);
				}
				// Check if edge has been processed
				if (!m_processed[vi.first][vi.second])
				{
					process_edge(vi);
				}
			}
		}
	}
}

// fails if neighbor is wall
bool valid_edge(const pair<int, int>& v, const pair<int, int>& a)
{
	pair<int, int> result = pair<int, int>(v.first + a.first, v.second + a.second);
	if (result.first < 0 || result.second < 0 || result.first >= 50 || result.second >= 50)
		return false;

	return (nodes[v.first + a.first][v.second + a.second].type != 0);
}





void process_vertex(const pair<int, int>& v) { }
void process_edge(const pair<int, int>& e) { }

void Prim(const pair<int, int> start)
{
	pair<int, int> parent[MAZE_SIZE][MAZE_SIZE];

	bool intree[MAZE_SIZE][MAZE_SIZE];		// is vertex in tree
	int distance[MAZE_SIZE][MAZE_SIZE];		// vertex distance from start
	pair<int, int> v;						// current vertex to process
	pair<int, int> w;						// candidate next vertex
	int weight;								// edge weight
	int dist;								// shortest current distance

	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			intree[i][j] = false;
			distance[i][j] = MAXINT;
			parent[i][j] = pair<int, int>(-1, -1);
		}
	}

	distance[start.first][start.second] = 0;
	v = pair<int, int>(start);

	while (intree[v.first][v.second] == false)
	{
		intree[v.first][v.second] = true;
		//for (int i = 0; i < )
	}
}