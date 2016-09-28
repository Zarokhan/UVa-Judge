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


	int weight = 0;
	pair<int, int> connection;	// Connection of important vector of nodes
};

Node nodes[MAZE_SIZE][MAZE_SIZE];
vector<Node*> important;	// Important nodes
vector<Edge> edges;			// Edges of important nodes(vertecies)

priority_queue<pair<int, int>> m_alien;
pair<int, int> m_start;

void ResetNodes();
void InitializeNodes(const int ySize, const int xSize);
void CalculateWeights();

/* BFS */
void BreadthFirstSearch(const pair<int, int> start);
void process_vertex(const pair<int, int>& v);
void process_edge(const pair<int, int>& e);
bool valid_edge(const pair<int, int>& v, const pair<int, int>& a);

/* Weights */
void GoDownPath(const pair<int, int>& closed, pair<int, int>& open, int& weight);

/* Prim */
void Prim(const pair<int, int> start);

#endif