#define _MYMAN_H_
#ifdef _MYMAN_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <utility>

#define MAZE_SIZE	50

#define MAXV		2500		// Max number of vertecies
#define MAXDEGREE	4		// Max vertex outdegree

using namespace std;

struct Edge
{
	int v;			// Neighbour vertex
	int weight;		// Edge weight

	Edge();
};

struct Graph
{
	Edge edges[MAXV + 1][MAXDEGREE];						// Adjacency info
	int degree[MAXV + 1];				// outdegree of each vertex
	int nvertices;						// number of vertecies
	int nedges;							// number of edges

	Graph();
	void insert_edge(const int& x, const int& y);
	void print();
};

char m_maze_c[MAZE_SIZE][MAZE_SIZE];	// Maze in character 2D array (matrix)
int m_maze[MAZE_SIZE][MAZE_SIZE];		// Adjacency matrix		(0 => Wall, 1 => Space, 2 => Alien, 3 => Spawn)
priority_queue<pair<int, int>> m_parent[MAZE_SIZE][MAZE_SIZE];
priority_queue<pair<int, int>> m_alien;

bool m_processed[MAZE_SIZE][MAZE_SIZE];		// Which verteces have been processed
bool m_discovered[MAZE_SIZE][MAZE_SIZE];	// Which verteces have been found
bool m_walked[MAZE_SIZE][MAZE_SIZE];

pair<int, int> m_start;
int m_steps;

void InitAdjacencyMatrix(const int ySize, const int xSize);

void BreadthFirstSearch();
void process_vertex(const pair<int, int>& v);
void process_edge(const pair<int, int>& e);
bool valid_edge(const pair<int, int>& v, const pair<int, int>& a);

void KillAliens();
void PutDownCoin(const pair<int, int>& tile);
void GoDownPath(const pair<int, int>& tile);

#endif