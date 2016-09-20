// 10608
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>>* groups;

// Checks if a
bool isInGroup(vector<int>& vec, const int& a)
{
	if (std::find(vec.begin(), vec.end(), a) != vec.end())
		return true;
	return false;
}

void isInOtherGroup(const int& a, const int& current, const int& max, bool& isInOtherGroup, int& groupIndex)
{
	for (int i = current + 1; i < groups->size(); ++i)
	{
		vector<int> vec = (*groups)[i];
		if (std::find(vec.begin(), vec.end(), a) != vec.end())
		{
			isInOtherGroup = true;
			groupIndex = i;
			return;
		}
	}
}

void swapOtherGroup(const int& indexA, const int& indexB)
{
	vector<int>& vecA = (*groups)[indexA];
	vector<int>& vecB = (*groups)[indexB];

	vecA.reserve(vecA.size() + vecB.size());
	vecA.insert(vecA.end(), vecB.begin(), vecB.end());
	
	vecB.clear();
}

void recursiveMethod(const int& fA, const int&fB, int& current, const int& max)
{
	// one group of friends
	vector<int>& vec = (*groups)[current];
	// Check if fA or fB contains 
	bool aIsInGroup = isInGroup(vec, fA);
	bool bIsInGroup = isInGroup(vec, fB);

	// If only one is in group add the otherone to the group
	// If both is in group do nothing
	if (aIsInGroup && !bIsInGroup)
	{
		// Check if fB is in another group
		bool otherGroup = false;
		int index = 0;
		isInOtherGroup(fB, current, max, otherGroup, index);

		if (otherGroup)
		{
			swapOtherGroup(current, index);
		}
		else
		{
			vec.push_back(fB);
			return;
		}
	}
	else if (!aIsInGroup && bIsInGroup)
	{
		// Check if fA is in another group
		bool otherGroup = false;
		int index = 0;
		isInOtherGroup(fA, current, max, otherGroup, index);

		if (otherGroup)
		{
			swapOtherGroup(current, index);
		}
		else
		{
			vec.push_back(fA);
			return;
		}
	}
	else if (!aIsInGroup && !bIsInGroup)
	{
		if (current < max-1)
		{
			++current;
			recursiveMethod(fA, fB, current, max);
		}
		else
		{
			vector<int>* vector = new std::vector<int>();
			vector->push_back(fA);
			vector->push_back(fB);
			groups->push_back(*vector);
		}
	}
}

int main()
{
	int test_cases;
	cin >> test_cases;

	for (int k = 0; k < test_cases; ++k)
	{
		int towns_citizens, pairs_people;
		cin >> towns_citizens >> pairs_people;

		groups = new std::vector<std::vector<int>>();
		for (int j = 0; j < pairs_people; j++)
		{
			int fA, fB; // FriendA, FriendB
			cin >> fA >> fB;
			
			// Add first group of friends
			if (j == 0)
			{
				vector<int> first_group;
				first_group.push_back(fA);
				first_group.push_back(fB);
				groups->push_back(first_group);
				continue;
			}

			int current = 0;
			int max = groups->size();
			recursiveMethod(fA, fB, current, max);
		}

		int biggest_group_of_friends = 0;
		for (int i = 0; i < groups->size(); i++)
		{
			int group_size = (*groups)[i].size();
			if (group_size > biggest_group_of_friends)
				biggest_group_of_friends = group_size;
		}
		cout << biggest_group_of_friends << endl;

		// clear groups
		groups->clear();
		if (groups->empty())
		{
			delete groups;
			groups = nullptr;
		}
	}

	return 0;
}

