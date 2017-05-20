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

using pos_type = decltype(std::sregex_iterator()->position());

struct section_info
{
	std::string id;
	std::string long_id;
	std::string filename;

	// offsets into the document
	pos_type beg;
	pos_type end;
};

std::string get_prog_name(std::string const& pathname)
{
	auto pos = pathname.find_last_of(path_separator());

	if(pos == std::string::npos)
		return pathname;

	return pathname.substr(pos + 1);
}

/// for all substrings `from` in `s` replace them with `to`
std::string& replace_all(std::string& s, std::string const& from, std::string const& to)
{
	if(!from.empty())
		for(std::size_t pos = 0; (pos = s.find(from, pos) + 1); pos += to.size())
			s.replace(--pos, from.size(), to);
	return s;
}

std::string urlencode(std::string const& url)
{
	static const std::string plain = "-_.";

	std::ostringstream oss;

	for(auto c: url)
	{
		if(std::isalnum(c) || plain.find(c) != std::string::npos)
			oss << c;
		else
			oss << "%" << std::uppercase << std::hex << int(c);
	}

	return oss.str();
}

/// Find all the section breaks in doc and store the relevant
/// info needed to split the document later
std::map<std::string, section_info> extract_section_info(std::string const& doc)
{
	std::map<std::string, section_info> sections; // long_id -> section

	// #1 long_id
	// #2 id
	// #3 name
	// #4 "Bibliography"
	std::regex const re_sec_text{R"~(#\s+(?:<a\s+name="(S-[^"]+)"></a>([\w\s-]+):\s+([\w -]+)|(Bibliography)))~"};

	std::sregex_iterator itr(std::begin(doc), std::end(doc), re_sec_text);
	std::sregex_iterator const itr_end;

	std::string filename = "";
	pos_type beg = 0;

	for(auto idx = 0U; itr != itr_end; ++itr, ++idx)
	{
		std::cout << "found: " << itr->str(3) << '\n';

		// #1 long_id
		// #2 id
		// #3 name
		// #4 "Bibliography"

		auto long_id = itr->str(4).empty() ? itr->str(1) : itr->str(4);

		if(beg)
		{
			auto& section = sections[long_id];

			section.id = itr->str(2).empty() ? std::string("") : itr->str(2);
			section.long_id = long_id;
			section.filename = filename;
			section.beg = beg;
			section.end = itr->position();
		}

		if(itr->str(4) == "Bibliography")
		{
			auto& section = sections["bibliography"];

			section.id = "Bib";
			section.long_id = "bibliography";
			section.filename = (idx < 10 ? "0":"") + std::to_string(idx) + "-Bibliography.md";
			section.beg = beg = itr->position();
			section.end = doc.size();
		}

		filename = (idx < 10 ? "0":"") + std::to_string(idx)
			+ (itr->str(2).empty() ? std::string("") : "-" + itr->str(2))
			+ (itr->str(3).empty() ? std::string("") : "-" + itr->str(3))
			+ ".md";

		beg = itr->position();
	}

	return sections;
}

/// Scan all the anchors in each section and build a URL out of it
std::map<std::string, std::string> build_link_database(std::string const& doc,
	std::map<std::string, section_info> const& sections)
{
	std::map<std::string, std::string> links;

	// build link database
	std::regex const e_anchors{R"~(<a\s+name="([^"]+)"></a>)~"};

	for(auto const& s: sections)
	{
		std::sregex_iterator itr_end;
		std::sregex_iterator itr{std::next(std::begin(doc), s.second.beg),
			std::next(std::begin(doc), s.second.end), e_anchors};

		for(; itr != itr_end; ++itr)
			links["](#" + itr->str(1) + ")"] = "](" + urlencode(s.second.filename) + '#' + itr->str(1) + ")";
	}

	return links;
}

void write(std::string const& dir, std::string const& filename, std::string const& text)
{
	auto pathname = dir + path_separator() + filename;
	std::cout << "generating: " << pathname << '\n';

	std::ostringstream index;
	index << "\n\n[INDEX](00-In-Introduction.md#SS-sec)\n\n";

	if(!(std::ofstream(pathname) << index.str() << text << index.str()))
		throw std::runtime_error(std::string(std::strerror(errno)) + ": " + filename);
}

/// Usage:
/// extract-sections <path-to-guidelines> [<output-dir>]opt
int main(int, char* argv[])
{
	auto prog = get_prog_name(argv[0]);

	try
	{
		if(!argv[1])
			throw std::runtime_error("Pathname for CppCoreGuidelines.md required");

		std::string const doc = [&]
		{
			std::ostringstream oss;
			if(!(oss << std::ifstream(argv[1]).rdbuf()))
				throw std::runtime_error(std::string(std::strerror(errno)) + ": " + argv[1]);
			return oss.str();
		}();

		std::string path = argv[2] ? argv[2]: ".";

		// section_id -> section
		auto sections = extract_section_info(doc);

		auto links = build_link_database(doc, sections);

		for(auto const& s: sections)
		{
			// extract section text from document
			std::string text = doc.substr(s.second.beg, s.second.end - s.second.beg);

			// rewrite links
			for(auto const& link: links)
				text = replace_all(text, link.first, link.second);

			write(path, s.second.filename, text);
		}
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
