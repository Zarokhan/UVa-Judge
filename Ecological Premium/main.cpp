// 10300
#pragma warning( disable : 4996 )
#include <iostream>
#include <vector>

int main(int args, char* arg[])
{
	int test_cases;
	std::cin >> test_cases;

	// Test cases need to be under 20
	if (test_cases >= 20) return 1;

	for (int j = 0; j < test_cases; j++)
	{
		int farmers;
		std::cin >> farmers;

		// 0 < farmers < 20
		if (farmers <= 0 || farmers >= 20) return 1;

		float sum = 0;

		for (int k = 0; k < farmers; k++)
		{
			int n = 0;
			int input;
			std::vector<int> vec;
			while (std::cin >> input)
			{
				vec.push_back(input);
				n++;
				if (n >= 3) break;
			}

			float spacePerAnimal = (float)vec[0] / (float)vec[1];
			float newvalue = spacePerAnimal * (float)vec[2];
			float price = newvalue * (float)vec[1];
			sum += price;
		}
		int answer = (int)sum;
		std::cout << answer << std::endl;
	}

	return 0;
}