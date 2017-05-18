/*
 * extract-sections.cpp
 *
 *  Created on: May 18, 2017
 *      Author: galik
 */

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <set>
#include <vector>

constexpr char path_separator()
{
#if defined _WIN32 || defined __CYGWIN__
    return '\\';
#else
    return '/';
#endif
}

// REGULAR EXPRESSIONS

// extract section names
//	 * [In: Introduction](#S-introduction)
//	 * [Glossary](#S-glossary)
//	 * [To-do: Unclassified proto-rules](#S-unclassified)
//
// #1 id
// #2 name
// #3 long_id (primary key)
std::regex const re_sec_names{R"~(\*\s+\[(?:([\w\s-]+):\s+)?([\w\s-]+)\]\(#(S-\w+)\))~"};

// # <a name="S-unclassified"></a>To-do: Unclassified proto-rules
// # <a name="S-glossary"></a>Glossary
// # Bibliography
// #1 long_id
// #2 id
// #3 name
// #4 "Bibliography"
std::regex const re_sec_text{R"~(#\s+(?:<a\s+name="(S-[^"]+)"></a>([\w\s-]+):\s+([\w -]+)|(Bibliography)))~"};

struct section
{
	std::string id;
	std::string name;
	std::string long_id;

	bool operator<(section const& s) const { return long_id < s.long_id; }
	bool operator==(section const& s) const { return long_id == s.long_id; }
};

std::string get_prog_name(std::string const& pathname)
{
	auto pos = pathname.find_last_of(path_separator());

	if(pos == std::string::npos)
		return pathname;

	return pathname.substr(pos + 1);
}

std::string get_path_name(std::string const& pathname)
{
	return pathname.substr(0, pathname.find_last_of(path_separator()));
}

void write(std::string const& dir, std::string const& filename, std::string const& text)
{
	auto pathname = dir + path_separator() + filename;
	std::cout << "pathnam: " << pathname << '\n';
	if(!(std::ofstream(pathname) << text))
		throw std::runtime_error(std::string(std::strerror(errno)) + ": " + filename);
}

int main(int, char* argv[])
{
	auto prog = get_prog_name(argv[0]);
	auto path = get_path_name(argv[0]); // directory to put results

	try
	{
		if(!argv[1])
			throw std::runtime_error("Pathname for CppCoreGuidelines.md required");

		std::string doc = [&]
		{
			std::ostringstream oss;
			if(!(oss << std::ifstream(argv[1]).rdbuf()))
				throw std::runtime_error(std::string(std::strerror(errno)) + ": " + argv[1]);
			return oss.str();
		}();

		std::sregex_iterator itr(std::begin(doc), std::end(doc), re_sec_text);
		std::sregex_iterator const itr_end;

		unsigned idx = 0;
		std::string previous_name = "";
		decltype(itr->position()) previous_position = 0;

		for(; itr != itr_end; ++itr, ++idx)
		{
			std::cout << '\n';

			for(auto i = 0U; i < itr->size(); ++i)
				std::cout << "match: " << i << ": " << itr->str(i) << '\n';

			// #1 long_id
			// #2 id
			// #3 name
			// #4 "Bibliography"

			if(!previous_position)
			{
				previous_name = (idx < 10 ? "0":"") + std::to_string(idx) + "-" + itr->str(2) + "-" + itr->str(3) + ".md";
				previous_position = itr->position();
			}
			else
			{
				// extract from previous position to this one

				std::string text = doc.substr(previous_position, itr->position() - previous_position);
				write(path, previous_name, text);

				previous_name = (idx < 10 ? "0":"") + std::to_string(idx) + "-" + itr->str(2) + "-" + itr->str(3) + ".md";
				previous_position = itr->position();
			}
		}

		// # Bibliography
		std::string text = doc.substr(previous_position, doc.size() - previous_position);
		write(path, "Bibliography.md", text);
	}
	catch(std::exception const& e)
	{
		std::cerr << prog << ": " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cerr << prog << ": unknown error" << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
