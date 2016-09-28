// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 10307
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#define MAZE_SIZE 50
#define INT_MAX 50000000

using namespace std;

struct Node {
	Node()
	{
		c = '#';
		type = 0;
		id = -1;
		walked = false;
	}
	~Node()
	{
	}

	char c;
	int type;
	int id;
	bool walked;
	pair<int, int> pos;
	pair<int, int> parent;
	vector<pair<int, Node*>> outdegree;	// each element = edge, f: Weight and other s:vertex  /* NEEDS TO BE SORTED */
};

struct Edge {
	Edge(int w) : weight(w) {}

	int weight = 0;
	pair<int, int> connection;	// Connection of important vector of nodes
	bool Edge::operator < (const Edge& a) const { return this->weight < a.weight; }
};

Node m_maze[MAZE_SIZE][MAZE_SIZE];
/* Two rows down my graph below */
vector<Node*> m_node;	// Important nodes
vector<Edge*> m_edge;		// Edges of important nodes(vertecies) (heap allocated)

void DisposeEdges()
{
	for (int i = 0; i < m_edge.size(); ++i)
		delete m_edge[i];
	m_edge.clear();
}

void ResetNodes();
void InitializeNodes(const int ySize, const int xSize, int& start);

/* BFS */
void BreadthFirstSearch(const pair<int, int> start);
void process_vertex(const pair<int, int>& v);
void process_edge(const pair<int, int>& e);
bool valid_edge(const pair<int, int>& v, const pair<int, int>& a);

/* Calculates the weight of the edge weights */
void CalculateWeights();
void GoDownPath(const pair<int, int>& closed, pair<int, int>& open, int& weight);

/* Sort Edges */
bool CompareByWeights(const Edge* a, const Edge* b) { return *a < *b; }

/* MST Prim's algorithm - shortest distance */
int Prim(int start);

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
				m_maze[k-1][n].c = c;
				++n;
			}
			n = 0;
		}
		int start = 0;
		int totalDistance = 0;
		InitializeNodes(y, x, start);
		CalculateWeights();
		// SORT HERE (SORT outdegree of all m_nodes)
		//sort(m_edge.begin(), m_edge.end(), CompareByWeights);

		if (m_edge.size() != 0)
			totalDistance = Prim(start);
		
		DisposeEdges();
		cout << totalDistance << endl;
	}
	

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
				m_maze[y2][x2].id = m_node.size();
				m_node.push_back(&m_maze[y2][x2]);
				break;
			case 'S':
				m_maze[y2][x2].type = 3;
				start = m_node.size();
				m_maze[y2][x2].id = m_node.size();
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

			in->outdegree.push_back(pair<int, Node*>(weight, jn));

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

int Prim(int start)
{
	const int MAXV = m_node.size();	//	Number of vertecies
	vector<bool> intree;			//	Is vertex already in tree
	vector<int> distance;			//	Vertex distance from start
	vector<int> parent;
	int v;							//	Current vertex to process
	int w;							//	Candidate next vertex
	int weight;						//	Edge weight
	int dist;						//	Shortest current distance

	for (int i = 0; i < MAXV; ++i)
	{
		intree.push_back(false);
		distance.push_back(INT_MAX);
		parent.push_back(-1);
	}

	distance[start] = 0;
	v = start;

	const int outdegree = m_node.size() - 1;	// Outdegree of each vertex

	while (intree[v] == false)
	{
		intree[v] = true;
		for (int i = 0; i < m_node[v]->outdegree.size(); ++i)
		{
			w = m_node[v]->outdegree[i].second->id;
			weight = m_node[v]->outdegree[i].first;
			if (distance[w] > weight && intree[w] == false)
			{
				distance[w] = weight;
				parent[w] = v;
			}
		}

		v = 1;
		dist = INT_MAX;
		for (int i = 2; i < m_node.size(); ++i)
		{
			if (intree[i] == false && dist > distance[i])
			{
				dist = distance[i];
				v = i;
			}
		}
	}

	int totalDistance = 0;
	for (vector<int>::iterator it = distance.begin(); it != distance.end(); ++it)
		totalDistance += *it;
	return totalDistance;
}