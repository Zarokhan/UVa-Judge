#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <set>
#include <assert.h>

// https://www.youtube.com/watch?v=BcaZIxaS-F4

template<class T>
class Graph
{
private:
	static const int MAXIMUM = 50;
	bool adjacencyMatrix[MAXIMUM][MAXIMUM];
	T labels[MAXIMUM];
	int countVertecies;
public:
	Graph();
	~Graph();

	void addVertex(const T& value);
	void addEdge(int source, int target);
	void removeEdge(int source, int target);
	T& operator [] (int vertex);
	T operator [] (int vertex) const;
	int size() { return countVertecies; }
	bool isEdge(int source, int target);
	std::set<int> neighbors(int vertex) const;
};

template <class T>
const int Graph<T>::MAXIMUM;

template<class T>
Graph<T>::Graph()
{
	for (int i = 0; i < MAXIMUM; i++)
	{
		for (int j = 0; j < MAXIMUM; j++)
		{
			adjacencyMatrix[i][j] = false;
		}
	}
	countVertecies = 0;
}

template<class T>
Graph<T>::~Graph()
{
}

template<class T>
void Graph<T>::addVertex(const T & value)
{
	assert(size() < MAXIMUM);
	int newVertexNumber = countVertecies;
	countVertecies++;

	for (int otherVertexNumber = 0; otherVertexNumber < countVertecies; ++otherVertexNumber)
	{
		adjacencyMatrix[otherVertexNumber][newVertexNumber] = false;
		adjacencyMatrix[newVertexNumber][otherVertexNumber] = false;
	}

	labels[newVertexNumber] = value;
}

template <class T>
void Graph<T>::addEdge(int source, int target)
{
	assert(source < size() && target < size());
	adjacencyMatrix[source][target] = true;
}

template<class T>
bool Graph<T>::isEdge(int source, int target)
{
	assert(source < size() && target < size());

	bool isAnEdge = false;
	isAnEdge = adjacencyMatrix[source][target];

	return isAnEdge;
}

template<class T>
T& Graph<T>::operator[](int vertex)
{
	assert(vertex < size());
	return &labels[vertex];
}

template<class T>
T Graph<T>::operator[](int vertex) const
{
	assert(vertex < size());
	return labels[vertex];
}

template<class T>
std::set<int> Graph<T>::neighbors(int vertex) const
{
	assert(vertex < size());
	std::set<int> vertexNeighbors;

	for (int index = 0; index < size(); index++)
	{
		if (adjacencyMatrix[vertex][index])
		{
			vertexNeighbors.insert(index);
		}
	}
	return vertexNeighbors;
}

template<class T>
void Graph<T>::removeEdge(int source, int target)
{
	assert(source < size() && target < size());
	adjacencyMatrix[source][target] = false;
}

#endif