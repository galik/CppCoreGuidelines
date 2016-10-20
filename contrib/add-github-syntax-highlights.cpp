/*
 * add-github-syntax-highlights.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: galik
 */

#include <string>
#include <iostream>

int main(int, char** argv)
{
	std::istream& is = std::cin;
	std::ostream& os = std::cout;

	try
	{
		bool in_dent = false;
		auto eol = "";

		for(std::string line; std::getline(is, line);)
		{
			if(!in_dent && !line.find("    "))
			{
				in_dent = true;
				os << eol << "```cpp";
				eol = "\n";
			}
			else if(in_dent && !line.empty() && line[0] != ' ')
			{
				in_dent = false;
				os << eol << "```";
				eol = "\n";
			}

			if(in_dent && line.size() > 3)
				line.erase(0, 4);

			os << eol << line;
			eol = "\n";
		}
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cerr << "Unknown exception." << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


