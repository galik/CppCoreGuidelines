/*
 * This file is released into the PUBLIC DOMAIN to be
 * copied and used in any manner whatsoever.
 *
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

#define con_out(m) do{std::cout << m << '\n';}while(0)
#define con_err(m) do{std::cerr << m << '\n';}while(0)

#define throw_runtime(m) do{std::ostringstream o;o<<m;throw std::runtime_error(o.str());}while(0)
#define throw_errno(m) throw_runtime(m << ": " << std::strerror(errno))

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

/// for all substrings `from` in `s` replace them with `to`
std::string& replace_all(std::string& s, std::string const& from, std::string const& to);

std::string urlencode(std::string const& url);

/// Find all the section breaks in doc and store the relevant
/// info needed to split the document later
std::map<std::string, section_info> extract_section_info(std::string const& doc);

/// Scan all the anchors in each section and build a URL out of it
std::map<std::string, std::string> build_link_database(std::string const& doc,
	std::map<std::string, section_info> const& sections);

void write(std::string const& dir, std::string const& filename, std::string const& text);

int usage(std::string const& prog, int error_code);

int main(int, char* argv[])
{
	std::string const prog = [argv]
	{
		std::string prog{argv[0]};
		if(auto pos = prog.rfind(path_separator()) + 1)
			prog.erase(0, pos);
		return prog;
	}();

	try
	{
		std::string pathname;
		std::string dir;

		for(auto arg = argv + 1; *arg; ++arg)
		{
			if(!std::strcmp(*arg, "-h") || !std::strcmp(*arg, "--help"))
				return usage(prog, EXIT_SUCCESS);
			else if((*arg)[0] == '-')
				throw_runtime("unknown option: " << *arg);
			else if(pathname.empty())
				pathname = *arg;
			else if(dir.empty())
				dir = *arg;
		}

		if(pathname.empty())
			throw_runtime("Pathname for CppCoreGuidelines.md required");

		if(dir.empty())
			dir = ".";

		std::string const doc = [&]
		{
			std::ostringstream oss;
			if(!(oss << std::ifstream(pathname).rdbuf()))
				throw_errno(argv[1]);
			return oss.str();
		}();

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

			write(dir, s.second.filename, text);
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

int usage(std::string const& prog, int error_code)
{

	con_out("");
	con_out("Usage: " << prog << " <input.md> [<out-dir>]");
	con_out("       " << prog << " -h|--help");
	con_out("");
	con_out("                If no output directory <out-dir> is specified");
	con_out("                  the output goes to the current directory.");
	con_out("");
	con_out("OPTIONS");
	con_out("");
	con_out(" -h|--help    - Print this help massage.");
	con_out("");

	return error_code;
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
		con_out("found: " << itr->str(3));

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
	con_out("generating: " << pathname);

	std::ostringstream index;
	index << "\n\n[INDEX](00-In-Introduction.md#SS-sec)\n\n";

	if(!(std::ofstream(pathname) << index.str() << text << index.str()))
		throw_errno(filename);
}
