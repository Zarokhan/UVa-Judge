// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 839
#include <iostream>

struct Node {
	int m_w_l;		// weight left
	int m_w_r;		// weight right
	int m_d_l;		// distance left of pivot point
	int m_d_r;		// distance right of pivot point

	Node(int w_l, int w_r, int d_l, int d_r) : m_w_l(w_l), m_w_r(w_r), m_d_l(d_l), m_d_r(d_r) {}

	Node* m_left = NULL;
	Node* m_right = NULL;

	bool IsBalanced()
	{
		bool children_balanced;
		if (m_w_l == 0)
		{
			children_balanced = m_left->IsBalanced();
			if (!children_balanced)
				return false;
		}
		if (m_w_r == 0)
		{
			children_balanced = m_right->IsBalanced();
			if (!children_balanced)
				return false;
		}

		return (GetLeftWeight() * m_d_l == GetRightWeight() * m_d_r) ? true : false;
	}
	int GetLeftWeight() { return (m_w_l == 0) ? m_left->GetLeftWeight() + m_left->GetRightWeight() : m_w_l; }
	int GetRightWeight() { return (m_w_r == 0) ? m_right->GetLeftWeight() + m_right->GetRightWeight() : m_w_r; }
};

// Insert
Node* AddNode()
{
	int w_l, d_l, w_r, d_r;					// Weight and distance variables
	std::cin >> w_l >> d_l >> w_r >> d_r;	// Get values

	Node* node = new Node(w_l, w_r, d_l, d_r);

	// Add left of node
	if (w_l == 0)
	{
		node->m_left = AddNode();
	}
	// Add right of node
	if (w_r == 0)
	{
		node->m_right = AddNode();
	}

	return node;
}

int main(int args, char* arg[])
{
	int test_cases;
	std::cin >> test_cases;

	Node* root;
	for (int test = 0; test < test_cases; ++test)
	{
		root = NULL;
		root = AddNode();
		bool balanced = root->IsBalanced();
		if (balanced)
			std::cout << "YES" << std::endl;
		else
			std::cout << "NO" << std::endl;
		if (test != test_cases - 1)
			std::cout << std::endl;
	}

	return 0;
}