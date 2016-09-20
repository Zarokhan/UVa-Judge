// 591
#include <iostream>
#include <vector>

int main(int args, char* arg[])
{
	int set = 0;
	int stacks;
	while (std::cin >> stacks)
	{
		if (stacks == 0)
			return 0;

		std::vector<int> stack;
		int nrofbricks = 0;
		int input = 0;

		int n = 0;
		while (std::cin >> input)
		{
			nrofbricks += input;
			stack.push_back(input);
			n++;
			if (n >= stacks) break;
		}

		int bricksPerStack = nrofbricks / stacks;
		int bricksRemoved = 0;

		// Remainder, take from the piles that has too many
		for (int i = 0; i < stack.size(); i++)
		{
			if (stack[i] > bricksPerStack)
				bricksRemoved += stack[i] - bricksPerStack;
		}

		set++;
		std::cout << "Set #" << set << std::endl;
		std::cout << "The minimum number of moves is " << bricksRemoved << "." << std::endl;
		std::cout << std::endl;
	}
	return 0;
}