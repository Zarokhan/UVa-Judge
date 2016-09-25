// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 10307
#include "myman.h"

int main(int args, char* arg[])
{
	int test_cases;
	cin >> test_cases;

	int y;				// Rows of input
	int x;				// Number of characters in each row
	string input;	// Line input
	char c;				// Character in line
	int n = 0;			// Index for iterator

	// For each test case
	for (int j = 0; j < test_cases; ++j)
	{
		cin >> x >> y;
		for (int k = 0; k < y+1; ++k) 
		{
			// Get maze input
			getline(cin, input);
			for (string::iterator it = input.begin(); it != input.end(); ++it)
			{
				c = *it;
				m_maze_c[k-1][n] = c;
				++n;
			}
			n = 0;
		}
		m_steps = 0;
		// Calculate shortest distance
		InitAdjacencyMatrix(y, x);
		BreadthFirstSearch();
		KillAliens();

		// Clear aliens
		while (!m_alien.empty())
			m_alien.pop();

		// output answer
		cout << m_steps << endl;
	}

	return 0;
}

void InitAdjacencyMatrix(const int ySize, const int xSize)
{
	Graph g;
	// Calculate adjacency matrix
	for (int y2 = 0; y2 < ySize; ++y2)
	{
		for (int x2 = 0; x2 < xSize; ++x2)
		{
			switch (m_maze_c[y2][x2])
			{
			case ' ':
				m_maze[y2][x2] = 1;
				g.insert_edge(y2, x2);
				break;
			case 'A':
				m_maze[y2][x2] = 2;
				m_alien.push(pair<int, int>(y2, x2));
				g.insert_edge(y2, x2);
				break;
			case 'S':
				m_maze[y2][x2] = 3;
				m_start.first = y2;
				m_start.second = x2;
				g.insert_edge(y2, x2);
				break;
			default:
				m_maze[y2][x2] = 0;
				break;
			}
			// Reset other properties
			m_processed[y2][x2] = false;
			m_discovered[y2][x2] = false;
			m_walked[y2][x2] = false;
			while (!m_parent[y2][x2].empty())
				m_parent[y2][x2].pop();
		}
	}

	g.print();
}

void BreadthFirstSearch()
{
	queue<pair<int, int>> q;	// Queue of vertices to visit
	pair<int, int> v;				// Current vertex

									// Enqueue first vertex
	q.push(m_start);
	m_discovered[m_start.first][m_start.second] = true;

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
				a.first = -1;
				break;
			case 2:
				a.second = 1;
				break;
			case 3:
				a.second = -1;
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
					m_parent[vi.first][vi.second].push(pair<int, int>(v));
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
	return (m_maze[v.first + a.first][v.second + a.second] != 0);
}

void process_vertex(const pair<int, int>& v) { }
void process_edge(const pair<int, int>& e) { }

void KillAliens()
{
	while (!m_alien.empty())
	{
		GoDownPath(m_alien.top());
		m_alien.pop();
	}
}

void GoDownPath(const pair<int, int>& tile)
{
	if (tile.first == m_start.first && tile.second == m_start.second)
		return;

	PutDownCoin(tile);
	// Check parent tile
	GoDownPath(m_parent[tile.first][tile.second].top());
}

void PutDownCoin(const pair<int, int>& tile)
{
	if (!m_walked[tile.first][tile.second])
	{
		m_walked[tile.first][tile.second] = true;
		++m_steps;
	}
}

Graph::Graph()
{
	this->nvertices = 0;
	this->nedges = 0;

	for (int i = 0; i < MAXV; ++i)
		this->degree[i] = 0;
}

void Graph::insert_edge(const int & x, const int & y)
{
	if (degree[x] > MAXDEGREE)
		printf("Warning: insertion(%d, %d) exceed max degree\n", x, y);

	edges[x][degree[x]] = Edge();
	++degree[x];
	++nedges;
}

void Graph::print()
{
	for (int i = 0; i < nvertices; ++i)
	{
		printf("%d: ", i);
		for (int j = 0; j < degree[i]; ++j)
			printf(" %d", edges[i][j]);
		printf("\n");
	}
}

Edge::Edge()
{
	v = 0;
	weight = 0;
}