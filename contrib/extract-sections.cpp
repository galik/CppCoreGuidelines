/*
 * This file is released into the PUBLIC DOMAIN to be
 * copied and used in any manner whatsoever.
 *
 * extract-sections.cpp
 *
 *  Created on: May 18, 2017
 *      Author: galik.bool@gmail.com
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

#include <hol/bug.h>

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

/**
 * For all substrings `from` in `s` replace them with `to`.
 * @param s The string to modify.
 * @param from The sunbtring to change.
 * @param to The replacement text.
 * @return The same `std::string` with substrings replaced.
 */
std::string& replace_all(std::string& s, std::string const& from, std::string const& to);

/**
 * Make the URL internet safe
 * @param url The URL to encode
 * @return Properly encoded URL
 */
std::string urlencode(std::string const& url);

/// Find all the section breaks in doc and store the relevant
/// info needed to split the document later
std::map<std::string, section_info> extract_section_info(std::string const& doc);

/// Scan all the anchors in each section and build a URL out of it
std::map<std::string, std::string> build_link_database(std::string const& doc,
	std::map<std::string, section_info> const& sections);

void write(std::string const& dir, std::string const& filename, std::string const& text);

int usage(std::string const& prog, int error_code);

/**
 * Extract only the program name from the full path
 * @param pathname The full path name used to run the program
 * @return Just the program name
 */
std::string program_name(std::string pathname)
{
	if(auto pos = pathname.rfind(path_separator()) + 1)
		pathname.erase(0, pos);
	return pathname;
}

/**
 * Load a file into a `std::string`.
 * @param pathname pathname of file.
 * @return A `std::string` containing the file.
 */
std::string load_file(std::string const& pathname)
{
	std::ostringstream oss;

	if(!(oss << std::ifstream(pathname).rdbuf()))
		throw_errno(pathname);

	return oss.str();
}

/**
 * Keep track of line endings.
 */
class line_ender
{
public:
	line_ender() {}

private:
	char const* eol = "";

	friend std::ostream& operator<<(std::ostream& o, line_ender& le)
	{
		o << le.eol;
		le.eol = "\n";
		return o;
	}
};

/**
 * Modify Markdown code sections to use GitHub specific
 * syntax highlights
 * @param doc The Markdown document data.
 * @return The modified document.
 */
std::string add_syntax_heighlights(std::string const& doc)
{
	line_ender eol;
	bool indented = false;

	std::istringstream is(doc);
	std::ostringstream os;

	for(std::string line; std::getline(is, line);)
	{
		if(!indented && !line.find("    "))
		{
			indented = true;
			os << eol << "```cpp";
		}
		else if(indented && !line.empty() && line[0] != ' ')
		{
			indented = false;
			os << eol << "```";
		}

		if(indented && line.size() > 3)
			line.erase(0, 4);

		os << eol << line;
	}

	return os.str();
}

int main(int, char* argv[])
{
	std::string const prog = program_name(argv[0]);

	try
	{
		enum class output_type{document, sections, items};

		std::string pathname;
		std::string dir;
		bool syntax_colors = false;

		std::set<output_type> outputs;

		for(auto arg = argv + 1; *arg; ++arg)
		{
			if(!std::strcmp(*arg, "-h") || !std::strcmp(*arg, "--help"))
				return usage(prog, EXIT_SUCCESS);
			else if(!std::strcmp(*arg, "-c") || !std::strcmp(*arg, "--color"))
				syntax_colors = true;
			else if(!std::strcmp(*arg, "-d") || !std::strcmp(*arg, "--document"))
				outputs.insert(output_type::document);
			else if(!std::strcmp(*arg, "-s") || !std::strcmp(*arg, "--sections"))
				outputs.insert(output_type::sections);
			else if(!std::strcmp(*arg, "-i") || !std::strcmp(*arg, "--items"))
				outputs.insert(output_type::items);
			else if((*arg)[0] == '-')
				throw_runtime("unknown option: " << *arg);
			else if(pathname.empty())
				pathname = *arg;
			else if(dir.empty())
				dir = *arg;
		}

		if(outputs.empty())
			outputs.insert(output_type::document);

		if(pathname.empty())
			throw_runtime("Pathname for CppCoreGuidelines.md required");

		if(dir.empty())
			dir = ".";

		con_out("Loading: " << pathname);

		if(syntax_colors)
			con_out("Colorizing:");

		std::string const doc = syntax_colors
			? add_syntax_heighlights(load_file(pathname))
			: load_file(pathname);

		if(outputs.count(output_type::document))
		{
			auto new_pathname = dir + path_separator() + program_name(pathname);

			// TODO: Use <filesystem> to makes this more reliable
			if(new_pathname == pathname)
				throw_runtime("can not overwrite the original, specify a different directory");

			con_out("Outputting document: " << new_pathname);
			if(!(std::ofstream(new_pathname) << doc))
				throw_errno(new_pathname);
		}

		if(outputs.count(output_type::sections)
		|| outputs.count(output_type::items))
		{
			con_out("Outputting sections:");
			// section_id -> section
			auto sections = extract_section_info(doc);

			// output one file for each section
			// 00-Section Name 0.md
			// 01-Section Name 1.md
			// 02-Section Name 2.md
			if(outputs.count(output_type::sections))
			{
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

			// output one file for the section index
			// and one file for each item
			// 02-Section Name 2-AB.00-index.md
			// 02-Section Name 2-AB.01.md
			if(outputs.count(output_type::items))
			{
				con_out("Outputting items:");
//				auto links = build_link_database(doc, sections);
//
//				for(auto const& s: sections)
//				{
//					// extract section text from document
//					std::string text = doc.substr(s.second.beg, s.second.end - s.second.beg);
//
//					// rewrite links
//					for(auto const& link: links)
//						text = replace_all(text, link.first, link.second);
//
//					write(dir, s.second.filename, text);
//				}
			}
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
	con_out("Usage: " << prog << " [OPTIONS] <input.md> [<out-dir>]");
	con_out("");
	con_out("                If no output directory <out-dir> is specified");
	con_out("                  the output goes to the current directory.");
	con_out("");
	con_out("OPTIONS");
	con_out("");
	con_out(" -h|--help     - Print this help massage.");
	con_out(" -c|--color    - Output GitHub syntax coloring.");
	con_out(" -d|--document - Output the whole document.");
	con_out(" -s|--sections - Output a file for each document section.");
	con_out(" -i|--items    - Output a file for each section item.");
	con_out(" -h|--help     - Print this help massage.");
	con_out("");

	//	else if(!std::strcmp(*arg, "-c") || !std::strcmp(*arg, "--color"))
	//		syntax_colors = true;
	//	else if(!std::strcmp(*arg, "-d") || !std::strcmp(*arg, "--document"))
	//		output = output_type::document;
	//	else if(!std::strcmp(*arg, "-s") || !std::strcmp(*arg, "--sections"))
	//		output = output_type::sections;
	//	else if(!std::strcmp(*arg, "-i") || !std::strcmp(*arg, "--items"))
	//		output = output_type::items;

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
			+ (itr->str(3).empty() ? std::string("") : "-" + itr->str(3));

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
	bug_fun();
	auto pathname = dir + path_separator() + filename + ".md";
	con_out("generating: " << pathname);

	std::ostringstream index;
	index << "\n\n[INDEX](00-In-Introduction.md#SS-sec)\n\n";

//	if(!(std::ofstream(pathname) << index.str() << text << index.str()))
//		throw_errno(filename);
}
