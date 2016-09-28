// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 10307
#include "myman.h"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

int main(int args, char* arg[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
				m_maze[k-1][n].c = c;
				++n;
			}
			n = 0;
		}
		int start = 0;
		InitializeNodes(y, x, start);
		CalculateWeights();
		std::sort(m_edge.begin(), m_edge.end(), CompareByWeights);
		Prim(start);
	}
	DisposeEdges();

	return 0;
}

void ResetNodes()
{
	for (int i = 0; i < MAZE_SIZE; ++i)
	{
		for (int j = 0; j < MAZE_SIZE; ++j)
		{
			m_maze[i][j] = Node();
		}
	}

	m_node.clear();

	DisposeEdges();

	m_edge.clear();
}

void InitializeNodes(const int ySize, const int xSize, int& start)
{
	// Calculate adjacency matrix
	for (int y2 = 0; y2 < ySize; ++y2)
	{
		for (int x2 = 0; x2 < xSize; ++x2)
		{
			m_maze[y2][x2].pos = pair<int, int>(y2, x2);

			switch (m_maze[y2][x2].c)
			{
			case ' ':
				m_maze[y2][x2].type = 1;
				break;
			case 'A':
				m_maze[y2][x2].type = 2;
				m_node.push_back(&m_maze[y2][x2]);
				break;
			case 'S':
				m_maze[y2][x2].type = 3;
				start = m_node.size();
				m_node.push_back(&m_maze[y2][x2]);
				break;
			}
		}
	}

}

void CalculateWeights()
{
	for (int i = 0; i < m_node.size(); ++i)
	{
		Node* in = m_node[i];
		BreadthFirstSearch(in->pos);	//	VERY IMPORTANT THIS STAYS IN THE FIRST LOOP
										//	IF IN SECOND LOOP, GG LIFE INTEL PENTIUM
		for (int j = 0; j < m_node.size(); ++j)
		{
			Node* jn = m_node[j];
			if (in == jn)
				continue;

			int weight = 0;
			GoDownPath(in->pos, jn->pos, weight);

			/* ADDS EDGE HERE*/
			Edge* e = new Edge(weight);
			e->connection = pair<int, int>(i, j);
			m_edge.push_back(e);
		}
	}

}

void GoDownPath(const pair<int, int>& closed, pair<int, int>& open, int & weight)
{
	if (closed == open)
		return;

	++weight;
	pair<int, int> p = m_maze[open.first][open.second].parent;
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
	pair<int, int> v;			// Current vertex

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
					m_maze[vi.first][vi.second].parent = pair<int, int>(v);
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
	if (result.first < 0 || result.second < 0 || result.first >= MAZE_SIZE || result.second >= MAZE_SIZE)
		return false;

	return (m_maze[v.first + a.first][v.second + a.second].type != 0);
}

void process_vertex(const pair<int, int>& v) { }
void process_edge(const pair<int, int>& e) { }

void Prim(int start)
{

}