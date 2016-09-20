// 10878
// http://www.ascii-code.com/
// http://www.binaryhexconverter.com/binary-to-decimal-converter
#include <iostream>
#include <string>

int main(int args, char* arg[])
{
	std::string input;
	std::string answer;
	std::getline(std::cin, input);

	while (std::getline(std::cin, input))
	{
		std::string bin;

		bool breakpls = false;
		for (std::string::iterator it = input.begin(); it != input.end(); ++it)
		{
			char c = *it;

			if (c == ' ')
				bin.append("0");
			else if (c == 'o')
				bin.append("1");

			if (c == '_')
				breakpls = true;
		}

		if (breakpls)
			break;

		// convert long binary
		if (!bin.empty())
		{
			int li_bin = std::stol(bin, nullptr, 2);
			char c = li_bin;
			answer.append(1, c);
		}
	}
	std::cout << answer;
	return 0;
}