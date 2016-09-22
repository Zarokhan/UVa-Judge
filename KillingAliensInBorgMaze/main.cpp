// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 10307
#include <iostream>
#include <string>
#include <queue>
#include <utility>
#define MAZE_SIZE 50

using namespace std;

char m_maze_c[MAZE_SIZE][MAZE_SIZE];	// Maze in character 2D array (matrix)
int m_maze[MAZE_SIZE][MAZE_SIZE];		// Adjacency matrix		(0 => Wall, 1 => Space, 2 => Alien, 3 => Spawn)
priority_queue<pair<int, int>> m_parent[MAZE_SIZE][MAZE_SIZE];
priority_queue<pair<int, int>> m_alien;

bool m_processed[MAZE_SIZE][MAZE_SIZE];		// Which verteces have been processed
bool m_discovered[MAZE_SIZE][MAZE_SIZE];	// Which verteces have been found
bool m_walked[MAZE_SIZE][MAZE_SIZE];

pair<int, int> m_start;
int m_steps;

void PutDownCoin(const pair<int, int>& tile)
{
	if (!m_walked[tile.first][tile.second])
	{
		m_walked[tile.first][tile.second] = true;
		++m_steps;
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

void KillAliens()
{
	while (!m_alien.empty())
	{
		GoDownPath(m_alien.top());
		m_alien.pop();
	}
}

bool valid_edge(const pair<int, int>& v, const pair<int, int>& a)
{
	// return falls if neighbor is wall
	return (m_maze[v.first + a.first][v.second + a.second] != 0);
}

void process_vertex(const pair<int, int>& v)
{
}

void process_edge(const pair<int, int>& e)
{
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
				pair<int, int> valid_i(v.first + a.first, v.second + a.second);
				// Check if it's discovered
				if (!m_discovered[valid_i.first][valid_i.second]) {
					// Enqueue valid undiscovered vertex
					q.push(pair<int, int>(valid_i.first, valid_i.second));
					m_discovered[valid_i.first][valid_i.second] = true;
					m_parent[valid_i.first][valid_i.second].push(pair<int, int>(v));
				}
				// Check if edge has been processed
				if (!m_processed[valid_i.first][valid_i.second])
				{
					process_edge(valid_i);
				}
			}
		}
	}
}

void InitAdjacencyMatrix(const int ySize, const int xSize)
{
	// Calculate adjacency matrix
	for (int y2 = 0; y2 < ySize; ++y2)
	{
		for (int x2 = 0; x2 < xSize; ++x2)
		{
			switch (m_maze_c[y2][x2])
			{
			case ' ':
				m_maze[y2][x2] = 1;
				break;
			case 'A':
				m_maze[y2][x2] = 2;
				m_alien.push(pair<int, int>(y2, x2));
				break;
			case 'S':
				m_maze[y2][x2] = 3;
				m_start.first = y2;
				m_start.second = x2;
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
}

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