#ifndef _MYMAN_H_
#define _MYMAN_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <utility>
#include <vector>

#define MAZE_SIZE 50
#define MAXINT 5000000

using namespace std;

struct Node {
	Node()
	{
		c = '#';
		type = 0;
		walked = false;
		weight = 0;
		dist = MAXINT;
	}
	~Node()
	{
	}

	char c;
	int type;
	bool walked;
	int weight;
	int dist;
	pair<int, int> pos;
	pair<int, int> parent;
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

/* MST Prim's algorithm */
void Prim(int start);

#endif