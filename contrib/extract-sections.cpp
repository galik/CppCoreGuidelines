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

#define con_out(m) do{ std::cout << m << '\n'; }while(0)
#define con_err(m) do{ std::cerr << m << '\n'; }while(0)
#define bug(m) con_out(m);
#define bug_var(v) bug(#v ": " << v);

constexpr char path_separator()
{
#if defined _WIN32 || defined __CYGWIN__
    return '\\';
#else
    return '/';
#endif
}

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
	std::cout << "generating: " << pathname << '\n';
	if(!(std::ofstream(pathname) << text))
		throw std::runtime_error(std::string(std::strerror(errno)) + ": " + filename);
}

using pos_type = decltype(std::sregex_iterator()->position());

struct section
{
	std::string id;
	std::string long_id;
	std::string name;
	pos_type beg;
	pos_type end;
};

std::string& replace_all(std::string& s, std::string const& from, std::string const& to)
{
	if(!from.empty())
		for(std::size_t pos = 0; (pos = s.find(from, pos) + 1); pos += to.size())
			s.replace(--pos, from.size(), to);
	return s;
}

std::string urlencode(std::string const& url)
{
	static const std::string plain = "";
	std::ostringstream oss;
	std::string::const_iterator i = url.begin();
	for(; i != url.end(); ++i)
	{
		if(std::isalnum(*i) || plain.find(*i) != std::string::npos) { oss << *i; }
		else { oss << "%" << std::hex << int(*i); }
	}
	return oss.str();
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

		std::map<std::string, section> names; // long_id -> section

		// #1 long_id
		// #2 id
		// #3 name
		// #4 "Bibliography"
		std::regex const re_sec_text{R"~(#\s+(?:<a\s+name="(S-[^"]+)"></a>([\w\s-]+):\s+([\w -]+)|(Bibliography)))~"};

		std::sregex_iterator itr(std::begin(doc), std::end(doc), re_sec_text);
		std::sregex_iterator const itr_end;

		unsigned idx = 0;
		std::string name = "";
		pos_type beg = 0;

		for(; itr != itr_end; ++itr, ++idx)
		{
			std::cout << "found: " << itr->str(3) << '\n';

			// #1 long_id
			// #2 id
			// #3 name
			// #4 "Bibliography"

			bug_var(beg);

			if(beg)
			{
				auto& section = names[itr->str(1)];

				section.id = itr->str(2);
				section.long_id = itr->str(1);
				section.name = name;
				section.beg = beg;
				section.end = itr->position();
			}

			name = (idx < 10 ? "0":"") + std::to_string(idx)
				+ "-" + itr->str(2)
				+ "-" + itr->str(3)
				+ ".md";

			beg = itr->position();
		}

		std::map<std::string, std::string> links;

		// build link database
		std::regex const e_anchors{R"~(<a\s+name="([^"]+)"></a>)~"};
		for(auto const& p: names)
		{
			std::sregex_iterator itr{std::next(std::begin(doc), p.second.beg),
				std::next(std::begin(doc), p.second.end), e_anchors};
			std::sregex_iterator itr_end;

			for(; itr != itr_end; ++itr)
			{
				links['#' + itr->str(1)] = urlencode(p.second.name) + '#' + itr->str(1);
			}
		}

		// rewrite links
		for(auto const& p: names)
		{
			std::string text = doc.substr(p.second.beg, p.second.end - p.second.beg);

			for(auto const& link: links)
				text = replace_all(text, link.first, link.second);

			write(path, p.second.name, text);

		}

		// # Bibliography
		std::string text = doc.substr(beg, doc.size() - beg);

		for(auto const& link: links)
			text = replace_all(text, link.first, link.second);

		write(path, (idx < 10 ? "0":"") + std::to_string(idx) + "-Bibliography.md", text);
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
