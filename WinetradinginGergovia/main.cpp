// Robin Andersson, ae5929, paul.robin.andersson@gmail.com
// 11054
// http://www.algolist.net/Algorithms/Sorting/Quicksort
#include <iostream>
#define MAX 100000

using namespace std;

struct Node
{
	Node(int _i, int _w) : i(_i), w(_w) {}
	Node(const Node& n) : i(n.i), w(n.w) { }
	Node() { i = 0; w = 0; }

	int i;	// index
	int w;	// wine

	bool operator < (const Node& a) const { return this->w < a.w; }
	bool operator > (const Node& b) const { return this->w > b.w; }
};

void QuickSort(Node arr[], int left, int right)
{
	int i = left, j = right;
	const Node& pivot = arr[(left + right) / 2];

	while (i <= j)
	{
		while (arr[i] < pivot)
			++i;
		while (arr[j] > pivot)
			--j;
		
		if (i <= j)
		{
			Node tmp(arr[i]);
			arr[i] = arr[j];
			arr[j] = tmp;
			++i;
			--j;
		}
	}

	if (left < j)
		QuickSort(arr, left, j);
	if (i < right)
		QuickSort(arr, i, right);
}

Node n[MAX];

int main()
{
	int size = 0;

	while (true)
	{
		cin >> size;
		if (size == 0)
			return 0;

		for (int i = 0; i < size; ++i)
		{
			int w = 0;
			cin >> w;
			n[i] = Node(i, w);
		}


	}

	return 0;
}