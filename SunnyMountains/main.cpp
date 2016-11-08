// Robin Andersson, AE5929, TGSPA14h, paul.robin.andersson@gmail.com
// 920 - Sunny Mountains
#include <iostream>
#include <vector>
using namespace std;

struct Vec2
{
	Vec2() = default;
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	float x = 0, y = 0;
};

int main()
{
	int test_cases = 0;
	int coords_len = 0;

	cin >> test_cases;
	for (int i = 0; i < test_cases; ++i)
	{
		queue<Vec2> coords;
		cin >> coords_len;
		for (int j = 0; j < coords_len; ++j)
		{
			float x = 0, y = 0;
			cin >> x >> y;
			coords.push(Vec2(x, y));
		}

		int test = 0;
		// sort coords on x coordinate
		// Calc lenght of two points
	}
}