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

#ifdef NDEBUG
#define throw_exception(e, m) do{std::ostringstream o;o<<m;throw e(o.str());}while(0)
#else
#define throw_exception(e, m) do{ \
	std::ostringstream o; \
	o << __FILE__ << ":" << __LINE__ << ":error: " << m; \
	throw e(o.str());}while(0)
#endif // NDEBUG

#define throw_runtime_error(m) throw_exception(std::runtime_error, m)
#define throw_errno(m) throw_runtime_error(m << ": " << std::strerror(errno))

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
	unsigned index;
	std::string mini_id;
	std::string long_id;
	std::string name;

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

///// Find all the section breaks in doc and store the relevant
///// info needed to split the document later
//std::map<std::string, section_info> extract_section_info(std::string const& doc);

/// Find all the section breaks in doc and store the relevant
/// info needed to split the document later
std::vector<section_info> extract_section_info(std::string const& doc);

/// Scan all the anchors in each section and build a URL out of it
//std::map<std::string, std::string> build_link_database(std::string const& doc,
//	std::vector<section_info> const& sections);
std::vector<std::string> extract_links_from_anchors(std::string const& doc);

void output(std::string const& dir, std::string const& filename, std::string const& text);

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

inline
bool s_to_test(char const* s, char const* e)
{
	if(e == s)
		return false;

	while(std::isspace(*e))
		++e;

	return !(*e);
}

inline
bool s_to_ul(const std::string& s, unsigned& u)
{
	char* end;
	u = unsigned(std::strtoul(s.c_str(), &end, 10));
	return s_to_test(s.c_str(), end);
}

unsigned calc_line_number(std::string const& doc, pos_type pos)
{
	unsigned line_number = 0;
	std::istringstream iss(doc.substr(0, pos));

	for(std::string line; std::getline(iss, line);)
		++line_number;

	return line_number;
}

//std::string pad(std::string const& s, unsigned n, char padding = ' ')
//{
//	if(s.size() < n)
//		return std::string(n - s.size(), padding) + s;
//	return s;
//}

std::string pad(unsigned u, unsigned n, char padding = '0')
{
	auto s = std::to_string(u);
	if(s.size() < n)
		return std::string(n - s.size(), padding) + s;
	return s;
}

// "S-02-Section Name.md"
std::string make_section_filename(section_info const& s)
{
	return "S-" + pad(s.index, 2) + '-' + s.name + ".md";
}

// "I-02-Section Name-P.01.md"
std::string make_item_filename(section_info const& s, unsigned idx)
{
	return "I-" + pad(s.index, 2) + '-' + s.name
		+ '-' + s.mini_id + '.' + pad(idx, 3) + ".md";
}

std::string make_index_item(std::string const& text, std::string const& link)
{
	return "* [" + text + "](" + link + ")";
}

enum class output_type{document, sections, items};

struct config
{
	std::string pathname;
	std::string dir;
	bool use_syntax_colors = false;
	bool list_only = false;
	std::set<output_type> outputs;
	int exit_status = 2;
};

config parse_commandline(char const* const* argv);

void output_section_files(config const& cfg, std::string const& doc,
	std::vector<section_info> const& sections, std::vector<std::string> const& links);

void output_item_files(config const& cfg, std::string const& doc,
	std::vector<section_info> const& sections, std::vector<std::string> const& links);

int main(int, char* argv[])
{
	try
	{
		config cfg = parse_commandline(argv);

		if(cfg.exit_status != 2)
			return cfg.exit_status;

		if(cfg.outputs.empty())
			cfg.outputs.insert(output_type::document);

		if(cfg.pathname.empty())
			throw_runtime_error("Pathname for CppCoreGuidelines.md required");

		if(cfg.dir.empty())
			cfg.dir = ".";

		con_out("Loading: " << cfg.pathname);

		if(cfg.use_syntax_colors)
			con_out("Colorizing:");

		std::string const doc = cfg.use_syntax_colors
			? add_syntax_heighlights(load_file(cfg.pathname))
			: load_file(cfg.pathname);

		if(cfg.outputs.count(output_type::document))
		{
			auto new_pathname = cfg.dir + path_separator() + program_name(cfg.pathname);

			// TODO: Use <filesystem> to makes this more reliable
			if(new_pathname == cfg.pathname)
				throw_runtime_error("can not overwrite the original, specify a different directory");

			con_out("Outputting document: " << new_pathname);
			if(!cfg.list_only)
				if(!(std::ofstream(new_pathname) << doc))
					throw_errno(new_pathname);
		}

		if(cfg.outputs.count(output_type::sections)
		|| cfg.outputs.count(output_type::items))
		{
			con_out("Outputting sections:");
			// section_id -> section
			auto sections = extract_section_info(doc);
			auto links = extract_links_from_anchors(doc);

			// output one file for each section
			// 00-Index.md
			// 01-Section Name 1.md
			// 02-Section Name 2.md
			if(cfg.outputs.count(output_type::sections))
				output_section_files(cfg, doc, sections, links);

			// output one index file of all sections (section-index)
			// I-00-Index.md
			// output one index file of all items in each section (item-index)
			// I-01-Section Name 1-S1.00-index.md
			// I-02-Section Name 2-S2.00-index.md
			// and one file for each item
			// I-02-Section Name 2-AB.01.md
			if(cfg.outputs.count(output_type::items))
				output_item_files(cfg, doc, sections, links);
		}
	}
	catch(std::exception const& e)
	{
		con_err(program_name(argv[0]) << ": " << e.what());
		return EXIT_FAILURE;
	}
	catch(...)
	{
		con_err(program_name(argv[0]) << ": unknown error");
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

	return error_code;
}

config parse_commandline(char const* const* argv)
{
	config cfg;

	for(auto arg = argv + 1; *arg; ++arg)
	{
		if(!std::strcmp(*arg, "-h") || !std::strcmp(*arg, "--help"))
			cfg.exit_status = usage(program_name(argv[0]), EXIT_SUCCESS);
		else if(!std::strcmp(*arg, "-c") || !std::strcmp(*arg, "--color"))
			cfg.use_syntax_colors = true;
		else if(!std::strcmp(*arg, "-d") || !std::strcmp(*arg, "--document"))
			cfg.outputs.insert(output_type::document);
		else if(!std::strcmp(*arg, "-s") || !std::strcmp(*arg, "--sections"))
			cfg.outputs.insert(output_type::sections);
		else if(!std::strcmp(*arg, "-i") || !std::strcmp(*arg, "--items"))
			cfg.outputs.insert(output_type::items);
		else if(!std::strcmp(*arg, "-l") || !std::strcmp(*arg, "--list"))
			cfg.list_only = true;
		else if((*arg)[0] == '-')
			throw_runtime_error("unknown option: " << *arg);
		else if(cfg.pathname.empty())
			cfg.pathname = *arg;
		else if(cfg.dir.empty())
			cfg.dir = *arg;
	}

	return cfg;
}

void output_section_files(config const& cfg, std::string const& doc,
	std::vector<section_info> const& sections, std::vector<std::string> const& links)
{
//				auto links = build_link_database(doc, sections);

	// Index of all sections
	std::ofstream index_file("S-00-Index.md");

	for(auto const& s: sections)
	{
		auto filename = urlencode(make_section_filename(s));

		// update S-00-Index.md
		index_file << make_index_item(s.mini_id + ": " + s.name, filename + "#" + s.long_id);
		index_file << '\n';

		// extract section text from document
		std::string text = doc.substr(s.beg, s.end - s.beg);

		// rewrite links
		for(auto const& link: links)
			text = replace_all(text, "](#" + link + ")", "](" + filename + "#" + link + ")");

		if(!cfg.list_only)
		{
			std::string index = "\n[SECTIONS](S-00-Index.md)\n";
			output(cfg.dir, make_section_filename(s), index + text + index);
		}
	}
}

void output_item_files(config const& cfg, std::string const& doc,
	std::vector<section_info> const& sections, std::vector<std::string> const& links)
{
	con_out("Outputting items:");

	// Index of all section indexes
	std::string main_index_file_name = "I-00-Index.md";
	std::ofstream main_index_file(main_index_file_name);

	for(auto const& s: sections)
	{
		auto section_filename = make_section_filename(s);

		// I-01-Section Name 1-S1.00-index.md
		auto index_file_name = "I-" + pad(s.index, 2)
			+ '-' + s.name + "-" + s.mini_id + ".000-index.md";

		// update I-00-Index.md
		main_index_file << make_index_item(s.mini_id + ": " + s.name, index_file_name);
		main_index_file << '\n';

		// I-01-Section Name 1-S1.00-index.md
		std::ofstream index_file(index_file_name);
		index_file << "[SECTIONS](" + main_index_file_name + ")\n\n";

		// #1 item_id // unique
		// #2 mini_id // section mini_id
		// #3 number
		// #4 description
		// ### <a name="Ri-singleton"></a>I.3: Avoid singletons
		std::regex const e_item{R"~(#+\s+<a\s+name="([^"]+)"><\/a>([^.]+)\.(\d+):\s+(.*))~"};

		std::sregex_iterator itr_end;
		std::sregex_iterator itr(std::next(std::begin(doc), s.beg),
			std::next(std::begin(doc), s.end), e_item);

		pos_type pos = 0;
		std::string item_id;
		std::string mini_id;
		unsigned number = 0;
		std::string item_filename;
		std::string description;

		for(; itr != itr_end; ++itr)
		{
			std::string text = doc.substr(s.beg + pos, itr->position() - pos);

			if(!cfg.list_only)
			{
				std::string index;
				index += "[SECTIONS](" + main_index_file_name + ")";
				index += "[OTHER ITEMS](" + index_file_name + ")";
				output(cfg.dir, make_item_filename(s, number), index + '\n' + text + '\n' + index);
			}

			// update I-01-Section Name 1-S1.00-index.md
			if(!pos)
			{
				description = "Introduction";
				item_filename = make_item_filename(s, number);
			}

			index_file << make_index_item(s.mini_id + "." + std::to_string(number) + ": " + description,
				item_filename);
			index_file << '\n';

			pos = itr->position();
			item_id = itr->str(1);
			mini_id = itr->str(2);
			number = unsigned(std::stoul(itr->str(3)));
			description = itr->str(4);
			item_filename = make_item_filename(s, number);
		}
		index_file << "\n[SECTIONS](" + main_index_file_name + ")";
	}
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
std::vector<section_info> extract_section_info(std::string const& doc)
{
	bug_fun();
	std::vector<section_info> sections;

	// #1 long_id
	// #2 id
	// #3 name
	// #4 "Bibliography"
	std::regex const re_sec_text{R"~(#\s+(?:<a\s+name="(S-[^"]+)"></a>([\w\s-]+):\s+([\w -]+)|(Bibliography)))~"};

	std::sregex_iterator itr(std::begin(doc), std::end(doc), re_sec_text);
	std::sregex_iterator const itr_end;

	std::string name;
	pos_type beg = 0;
	std::string long_id;
	std::string mini_id;

	for(auto idx = 0U; itr != itr_end; ++itr, ++idx)
	{
		con_out("found: " << itr->str(3));

		// #1 long_id
		// #2 id
		// #3 name
		// #4 "Bibliography"

		if(beg)
		{
			sections.emplace_back();
			auto& section = sections.back();

			section.index = idx;
			section.mini_id = mini_id;
			section.long_id = long_id;
			section.name = name;
			section.beg = beg;
			section.end = itr->position();
		}

		if(itr->str(4) == "Bibliography")
		{
			sections.emplace_back();
			auto& section = sections.back();

			section.index = idx + 1;
			section.mini_id = "Bib";
			section.long_id = "bibliography";
			section.name = "Bibliography";
			section.beg = beg = itr->position();
			section.end = doc.size();
		}

		long_id = itr->str(4).empty() ? itr->str(1) : itr->str(4);

		mini_id = itr->str(2).empty() ? std::string("") : itr->str(2);


		name = itr->str(3);

		beg = itr->position();
	}

	return sections;
}

std::vector<std::string> extract_links_from_anchors(std::string const& doc)
{
	std::vector<std::string> links;

	// build link database
	std::regex const e_anchors{R"~(<a\s+name="([^"]+)"></a>)~"};

	std::sregex_iterator itr_end;
	std::sregex_iterator itr{std::begin(doc), std::end(doc), e_anchors};

	for(; itr != itr_end; ++itr)
		links.push_back(itr->str(1));

	return links;
}

void output(std::string const& dir, std::string const& filename, std::string const& text)
{
	auto pathname = dir + path_separator() + filename;

	con_out("outputting: " << pathname);
	if(!(std::ofstream(pathname) << text))
		throw_errno(filename);
}
