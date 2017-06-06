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
#include <tuple>

#include <gsl/gsl>

#include <hol/bug.h>

//----------------------------------------------------------------------------
// Macros
//

#define con_out(m) do{std::cout << m << '\n';}while(0)
#define con_err(m) do{std::cerr << m << '\n';}while(0)

#ifdef NDEBUG
#define DEBUG_ONLY_SECTION(code) do{}while(0)
#define throw_exception(e, m) do{std::ostringstream o;o<<m;throw e(o.str());}while(0)
#else
#define DEBUG_ONLY_SECTION(code) do{code}while(0)
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

//----------------------------------------------------------------------------
// Types
//
using pos_type = decltype(std::sregex_iterator()->position());

enum class output_type {document, sections, items};

struct program_config
{

	std::string output_dir;
	std::string pathname;
	bool use_syntax_colors = false;
	bool list_only = false;
	bool verbose = false;
	std::map<output_type, std::string> outputs; // type -> prefix

	enum { success = EXIT_SUCCESS, failure = EXIT_FAILURE, ready = 2};
	int exit_status = ready;

	explicit operator bool() const { return exit_status == ready; }
};

struct document_part
{
	std::string id;
	std::string filename;
	pos_type beg = 0;
	pos_type end = 0;
};

// anchor -> {id, filename, beg, end}
using document_part_map = std::map<std::string, document_part>;

// anchor -> filename
using document_link_map = std::map<std::string, std::string>;

//----------------------------------------------------------------------------
// Regular Expressions
//

auto const fast_n_loose = std::regex_constants::optimize | std::regex_constants::icase;

// #1 anchor
// #2 id
// #3 title
// #4 Biography
std::regex const e_sects{R"~((?:#\s+<a name="(main|S-[^"]+)"><\/a>(?:((?:[^\s:]| )+):\s+)?(.*)|#\s+(Bibliography)))~", fast_n_loose};

// #1 anchor
// #2 id
// #3 title
std::regex const e_items{R"~(###\s+<a name="([^"]+)"><\/a>(?:((?:[^\s:]| )+):\s+)?(.*))~", fast_n_loose};

// #1 anchor
std::regex const e_links{R"~(<a name="([^"]+)">)~", fast_n_loose};

std::regex const e_item_id{R"~((.*?)\.(\d+))~", fast_n_loose};

//----------------------------------------------------------------------------
// String Utilities
//

/**
 * For all substrings `from` in `s` replace them with `to`.
 *
 * @param s The string to modify.
 * @param from The sunbtring to change.
 * @param to The replacement text.
 *
 * @return The same `std::string` with substrings replaced.
 */
std::string& replace_all(std::string& s, std::string const& from, std::string const& to)
{
	if(!from.empty())
		for(std::size_t pos = 0; (pos = s.find(from, pos) + 1); pos += to.size())
			s.replace(--pos, from.size(), to);
	return s;
}

/**
 * Make the URL internet safe
 *
 * @param url The URL to encode
 *
 * @return Properly encoded URL
 */
std::string urlencode(std::string const& url)
{
	static std::string const plain = "-_.";

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

/**
 * Extract only the program name from the full path
 *
 * @param pathname The full path name used to run the program
 *
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
 *
 * @param pathname pathname of file.
 *
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
 * Add leading characters to a number to make its string width
 * at least w. Output as a `std::string`.
 *
 * @param n The number to pad.
 * @param width The minimum width.
 * @param padding The character to pad with.
 *
 * @return A padded string version of the number.
 */
std::string pad(unsigned n, unsigned width, char padding = '0')
{
	auto s = std::to_string(n);
	if(s.size() < width)
		return std::string(width - s.size(), padding) + s;
	return s;
}

//----------------------------------------------------------------------------
// Document processing
//

struct line_ender
{
	char const* eol = "";
	char const* operator()(){ auto s = eol; eol = "\n"; return s; }
};

/**
 * Modify Markdown code sections to use GitHub specific
 * syntax highlights
 *
 * @param doc The Markdown document data.
 *
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
			os << eol() << "```cpp";
		}
		else if(indented && !line.empty() && line[0] != ' ')
		{
			indented = false;
			os << eol() << "```";
		}

		if(indented && line.size() > 3)
			line.erase(0, 4);

		os << eol() << line;
	}

	return os.str();
}


std::size_t line_number(std::string const& doc, pos_type pos)
{
	std::size_t count = 1;

	std::istringstream iss{std::string{std::begin(doc), std::next(std::begin(doc), pos)}};
	for(std::string line; std::getline(iss, line);)
		++count;

	return count;
}

/**
 * Build a map linking every unique `target` to the output file
 * in which it exists so that `links` can be re-written later to
 * point to the `target` in the correct file.
 *
 * @param doc
 * @param parts
 *
 * @return
 */
document_link_map build_link_map(std::string const& doc, document_part_map parts)
{
	document_link_map links;

	for(auto const& part: parts)
	{
		auto part_beg = std::next(std::begin(doc), part.second.beg);
		auto part_end = std::next(std::begin(doc), part.second.end);

		std::sregex_iterator const e;
		std::sregex_iterator m{part_beg, part_end, e_links};

		for(; m != e; ++m)
			links[m->str(1)] = part.second.filename;
	}

	return links;
}

/**
 * Build a `document_part_map` of the document sections. The
 * Markdown document is scanned and the location of each section
 * anchor is recorded in a `std::map` where the section anchor target
 * is the key.
 *
 * @param doc The Markdown document to scan.
 *
 * @return A `document_part_map` containing the locations of each section in
 * the document along with their assigned file name and section `id`.
 */
document_part_map locate_document_sections(std::string const& doc)
{
	document_part_map parts;

	std::sregex_iterator const e;
	std::sregex_iterator m{std::begin(doc), std::end(doc), e_sects};

	std::string anchor;
	document_part part;

	for(auto idx = 0U; m != e; ++m, ++idx)
	{
		part.end = m->position();

		if(!anchor.empty())
			parts[anchor] = part;

		anchor = m->str(1);
		part.id = m->str(2);
		part.filename = pad(idx, 2) + '-' + (m->str(3).empty() ? m->str(4) : m->str(3));
		part.beg = m->position();
	}

	part.end = doc.size();
	parts[anchor] = part;

	return parts;
}

/**
 * Build a `document_part_map` of the document items. The
 * Markdown document is scanned one section at a time and the location
 * of each item anchor is recorded in a `std::map` where the item anchor target
 * is the key.
 *
 * @param doc The Markdown document to scan.
 * @param sections The map of all the sections enabling the document items to
 * be grouped according to section.
 *
 * @return A `document_part_map` containing the locations of each item in
 * the document along with their assigned file name and item `id`.
 */
document_part_map locate_document_items(std::string const& doc,
	document_part_map const& sections)
{
	document_part_map items;

	std::sregex_iterator const e;

	auto idx = 0U;

	for(auto const& section_pair: sections)
	{
		auto const& section_anchor = std::get<const std::string>(section_pair);
		auto const& section = std::get<document_part>(section_pair);

		auto const beg_itr = std::next(std::begin(doc), section.beg);
		auto const end_itr = std::next(std::begin(doc), section.end);

		std::sregex_iterator m{beg_itr, end_itr, e_items};

		// initialize item to this section's header (index) between
		// the start of the section and the start of the first item
		document_part item = section;
		std::string item_anchor = section_anchor;

		for(; m != e; ++m, ++idx)
		{
			if(m->str(2).empty())
				con_err("item is missing an item tag: " << line_number(doc, section.beg + m->position()) << ": " << m->str());

			item.end = section.beg + m->position();
			items[item_anchor] = item;

			item_anchor = m->str(1);
			item.id = m->str(2).empty() ? section.id : m->str(2);

			// pad any item id that ends in numbers to maintain
			// correct ordering when listing alphabetically
			std::string item_id = item.id;

			std::smatch sm;
			if(std::regex_match(item_id, sm, e_item_id))
				item_id = sm.str(1) + "." + pad(gsl::narrow<unsigned>(std::stoul(sm.str(2))), 3);

			item.filename = section.filename + "-" + item_id;
			item.beg = item.end;
		}

		item.end = section.end;
		items[item_anchor] = item;
	}

	return items;
}

/**
 * Print instructions to use the program.
 *
 * @param prog The name of the program as invoked on the command line.
 * @param error_code Whether to keep going, to exit normally or
 * to exit with an error code.
 *
 * @return The error_code provided asa parameter to the function.
 */
int usage(std::string const& prog, int error_code)
{
	con_out("");
	con_out("Usage: " << prog << " [OPTIONS] <input.md> [<out-dir>]");
	con_out("");
	con_out("Parse the CppCoreGuidelines.md file and output one or more of: ");
	con_out("  The processed document as a whole.");
	con_out("  The processed document broken down into sections.");
	con_out("  The processed document broken down into individual items.");
	con_out("");
	con_out("                If no output directory <out-dir> is specified");
	con_out("                  the output goes to the current directory.");
	con_out("");
	con_out("OPTIONS");
	con_out("");
	con_out(" -c|--color    - Output GitHub syntax coloring.");
	con_out(" -d|--document - Output the whole document.");
	con_out(" -h|--help     - Print this help massage.");
	con_out(" -i|--items    - Output a file for each section item.");
	con_out(" -s|--sections - Output a file for each document section.");
	con_out(" -v|--verbose  - Output more information.");
	con_out("");

	return error_code;
}

/**
 * Parse the command line options and build a `program_config` structure.
 *
 * @param argv Pased from `int main()`.
 *
 * @return The program's configuration file configured accirding to the
 * command line options..
 */
program_config parse_commandline(char const* const* argv)
{
	program_config cfg;

	for(auto arg = argv + 1; *arg; ++arg)
	{
		if(!std::strcmp(*arg, "-h") || !std::strcmp(*arg, "--help"))
			cfg.exit_status = usage(program_name(argv[0]), EXIT_SUCCESS);
		else if(!std::strcmp(*arg, "-d") || !std::strcmp(*arg, "--document"))
		{
			if(!*++arg)
				throw_runtime_error(*(arg - 1) << " requires an parameter");
			cfg.outputs[output_type::document] = *arg;
		}
		else if(!std::strcmp(*arg, "-s") || !std::strcmp(*arg, "--sections"))
		{
			if(!*++arg)
				throw_runtime_error(*(arg - 1) << " requires an parameter");
			cfg.outputs[output_type::sections] = *arg;
		}
		else if(!std::strcmp(*arg, "-i") || !std::strcmp(*arg, "--items"))
		{
			if(!*++arg)
				throw_runtime_error(*(arg - 1) << " requires an parameter");
			cfg.outputs[output_type::items] = *arg;
		}
		else if(!std::strcmp(*arg, "-c") || !std::strcmp(*arg, "--color"))
			cfg.use_syntax_colors = true;
		else if(!std::strcmp(*arg, "-l") || !std::strcmp(*arg, "--list"))
			cfg.list_only = true;
		else if(!std::strcmp(*arg, "-v") || !std::strcmp(*arg, "--verbose"))
			cfg.verbose = true;
		else if((*arg)[0] == '-')
			throw_runtime_error("unknown option: " << *arg);
		else if(cfg.pathname.empty())
			cfg.pathname = *arg;
		else if(cfg.output_dir.empty())
			cfg.output_dir = *arg;
	}

	return cfg;
}

int main(int, char* argv[])
{
	try
	{
		program_config cfg = parse_commandline(argv);

		if(!cfg)
			return cfg.exit_status;

		if(cfg.outputs.empty())
			cfg.outputs[output_type::document];

		if(cfg.pathname.empty())
			throw_runtime_error("Pathname for CppCoreGuidelines.md required");

		if(cfg.output_dir.empty())
			cfg.output_dir = ".";

		con_out("Loading: " << cfg.pathname);

		if(cfg.use_syntax_colors)
			con_out("Colorizing:");

		std::string const doc = cfg.use_syntax_colors
			? add_syntax_heighlights(load_file(cfg.pathname))
			: load_file(cfg.pathname);

		if(cfg.outputs.count(output_type::document))
		{
			auto new_pathname
				= cfg.output_dir
				+ path_separator()
				+ cfg.outputs[output_type::sections]
				+ program_name(cfg.pathname);

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
			// section information is needed by BOTH section & item output
			auto sections = locate_document_sections(doc);

			if(cfg.outputs.count(output_type::sections))
			{
				auto links = build_link_map(doc, sections);

				con_out("Outputting sections:");

				for(auto const& section: sections)
				{
					con_out("creating: " << section.second.filename);

					auto text = doc.substr(section.second.beg, section.second.end - section.second.beg);

					for(auto const& link: links)
						replace_all(text, "](#" + link.first + ")", "](" + cfg.outputs[output_type::sections] + urlencode(link.second) + ".md#" + link.first + ")");

					auto filepath
						= cfg.output_dir
						+ path_separator()
						+ cfg.outputs[output_type::sections]
						+ section.second.filename
						+ ".md";

					if(!(std::ofstream(filepath) << text))
						throw_errno(section.second.filename);
				}
			}

			if(cfg.outputs.count(output_type::items))
			{
				con_out("Outputting individual items:");

				auto items = locate_document_items(doc, sections);
				auto links = build_link_map(doc, items);

				for(auto const& item: items)
				{
					if(cfg.verbose)
						con_out("creating: " << item.second.filename);

					auto text = doc.substr(item.second.beg, item.second.end - item.second.beg);

					for(auto const& link: links)
						replace_all(text, "](#" + link.first + ")", "](" + cfg.outputs[output_type::items] + urlencode(link.second) + ".md#" + link.first + ")");

					auto filepath
						= cfg.output_dir
						+ path_separator()
						+ cfg.outputs[output_type::items]
						+ item.second.filename
						+ ".md";

					if(!(std::ofstream(filepath) << text))
						throw_errno(filepath);
				}
			}
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
