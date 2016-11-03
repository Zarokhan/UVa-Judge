#include <stack>
#include <Node>

#define M
#define n
#define cols
#define rows

struct Node;

using namespace std;

void DFS(const pair<int, int> v)
{
	stack<pair<int, int>> s;
	s.push(v);

	while (!s.empty())
	{
		Node& n = M[s.top().first][s.top().second];
		s.pop();

		if (!n.discovered)
		{
			n.discovered = true;
			pair<int, int> dim = pair<int, int>(n.d);

			if (dim.first < cols)
			{
				// Forward
				dim.first++;
				s.push(pair<int, int>(dim));
				n.n.push_back(pair<int, int>(dim));

				// left
				int valid = dim.second - 1;
				if (valid < 0)
					valid = rows - 1;

				s.push(pair<int, int>(dim.first, valid));
				n.n.push_back(pair<int, int>(dim.first, valid));

				// Right
				valid = dim.second + 1;
				if (valid + 1 >= rows)
					valid = 0;

				s.push(pair<int, int>(dim.first, valid));
				n.n.push_back(pair<int, int>(dim.first, valid));
			}
		}
	}
}