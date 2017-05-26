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

//----------------------------------------------------------------------------
// Types
//
using pos_type = decltype(std::sregex_iterator()->position());

enum class output_type{document, sections, items};

struct program_config
{
	std::string output_dir;
	std::string pathname;
	bool use_syntax_colors = false;
	bool list_only = false;
	bool verbose = false;
	std::set<output_type> outputs;
	int exit_status = 2;
};

struct document_part
{
	pos_type beg = 0;
	pos_type end = 0;
	std::string mini_id;
	std::string filename;
};

// link_id -> {filename, beg, end}
using document_part_map = std::map<std::string, document_part>;

// link_id -> filename
using document_link_map = std::map<std::string, std::string>;

//----------------------------------------------------------------------------
// Regular Expressions
//

auto const fast_n_loose = std::regex_constants::icase | std::regex_constants::optimize;

// #1 link_id
// #2 mini_id
// #3 title
std::regex const e_sects{R"~((?:#\s+<a name="(main|S-[^"]+)"><\/a>(?:((?:[^\s:]| )+):\s+)?(.*)|#\s+(Bibliography)))~", fast_n_loose};

// #1 link_id
// #2 mini_id
// #3 title
std::regex const e_items{R"~(###\s+<a name="([^"]+)"><\/a>(?:((?:[^\s:]| )+):\s+)?(.*))~", fast_n_loose};

// #1 link_id
std::regex const e_links{R"~(<a name="([^"]+)">)~", fast_n_loose};

//----------------------------------------------------------------------------
// String Utilities
//

/**
 * For all substrings `from` in `s` replace them with `to`.
 * @param s The string to modify.
 * @param from The sunbtring to change.
 * @param to The replacement text.
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
 * @param url The URL to encode
 * @return Properly encoded URL
 */
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
	struct line_ender
	{
		char const* eol = "";
		char const* operator()(){ auto out = eol; eol = "\n"; return out; }
	};

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

std::tuple<document_part_map, document_link_map> extract_document_sections(std::string const& doc)
{
	document_part_map parts;
	document_link_map links;

	std::sregex_iterator e;
	std::sregex_iterator m{std::begin(doc), std::end(doc), e_sects};

	std::string link_id;
	document_part part;

	for(auto idx = 0U; m != e; ++m, ++idx)
	{
		part.end = m->position();

		if(!link_id.empty())
			parts[link_id] = part;

		link_id = m->str(1);
		part.beg = m->position();
		part.mini_id = m->str(2);
		part.filename = pad(idx, 2) + '-' + (m->str(3).empty() ? m->str(4) : m->str(3));
	}

	part.end = doc.size();
	parts[link_id] = part;

	// TODO: factor this out
	for(auto const& p: parts)
	{
		std::sregex_iterator m
			{std::next(std::begin(doc), p.second.beg), std::next(std::begin(doc) + p.second.end), e_links};

		for(; m != e; ++m)
			links[m->str(1)] = p.second.filename;
	}

	return {parts, links};
}

std::size_t line_number(std::string const& doc, pos_type pos)
{
	std::size_t count = 1;

	std::istringstream iss{std::string{std::begin(doc), std::next(std::begin(doc), pos)}};
	for(std::string line; std::getline(iss, line);)
		++count;

	return count;
}


document_link_map build_link_map(std::string const& doc, document_part_map parts)
{
	document_link_map links;

	for(auto const& p: parts)
	{
		auto part_beg = std::next(std::begin(doc), p.second.beg);
		auto part_end = std::next(std::begin(doc), p.second.end);

		std::sregex_iterator const e;
		std::sregex_iterator m{part_beg, part_end, e_items};

		for(; m != e; ++m)
			links[m->str(1)] = p.second.filename;
	}

	return links;
}

// TODO: make this generic between sections and items (provide the ehole document for sections)
std::tuple<document_part_map, document_link_map> extract_document_items(std::string const& doc,
	std::tuple<document_part_map, document_link_map> const& section_info)
{
	document_part_map parts;
	document_link_map links;

	std::sregex_iterator const e;

	auto idx = 0U;

	for(auto const& section: std::get<document_part_map>(section_info))
	{
		auto section_beg = std::next(std::begin(doc), section.second.beg);
		auto section_end = std::next(std::begin(doc), section.second.end);

		std::sregex_iterator m{section_beg, section_end, e_items};

		// initialize for item's section header (index)
		document_part part = section.second; //{section.second.beg, section.second.end, section.second.mini_id, section.second.filename};
		std::string link_id = section.first;

		for(; m != e; ++m, ++idx)
		{
//			bug_var(m->str(3));
			if(m->str(2).empty())
				con_err("item is missing an item tag: " << line_number(doc, section.second.beg + m->position()) << ": " << m->str());

			part.end = section.second.beg + m->position();
			parts[link_id] = part;

			link_id = m->str(1);
			part.mini_id = m->str(2).empty() ? section.second.mini_id : m->str(2);

			bug_var(part.mini_id);
			std::regex e_mini{R"~(([^.]+)\.(\d+))~"};
			std::smatch sm;
			if(std::regex_match(part.mini_id, sm, e_mini))
				part.mini_id = sm.str(1) + "." + pad(gsl::narrow<unsigned>(std::stoul(sm.str(2))), 3);

			part.filename = section.second.filename + "-" + part.mini_id;
			part.beg = part.end;
		}

		part.end = section.second.end;
		parts[link_id] = part;
	}

	// TODO: factor this out
	for(auto const& p: parts)
	{
		auto part_beg = std::next(std::begin(doc), p.second.beg);
		auto part_end = std::next(std::begin(doc), p.second.end);

		std::sregex_iterator m{part_beg, part_end, e_items};

		for(; m != e; ++m)
			links[m->str(1)] = p.second.filename;
	}

	return {parts, links};
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
	con_out(" -c|--color    - Output GitHub syntax coloring.");
	con_out(" -d|--document - Output the whole document.");
	con_out(" -h|--help     - Print this help massage.");
	con_out(" -i|--items    - Output a file for each section item.");
	con_out(" -s|--sections - Output a file for each document section.");
	con_out(" -v|--verbose  - Output more information.");
	con_out("");

	return error_code;
}

program_config parse_commandline(char const* const* argv)
{
	program_config cfg;

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
	bug_fun();
	try
	{
		program_config cfg = parse_commandline(argv);

		if(cfg.exit_status != 2)
			return cfg.exit_status;

		if(cfg.outputs.empty())
			cfg.outputs.insert(output_type::document);

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
			auto new_pathname = cfg.output_dir + path_separator() + program_name(cfg.pathname);

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
			auto section_info = extract_document_sections(doc);

			if(cfg.outputs.count(output_type::sections))
			{
				con_out("Outputting sections:");

				for(auto const& part: std::get<document_part_map>(section_info))
				{
					con_out("creating: " << part.second.filename);

					auto text = doc.substr(part.second.beg, part.second.end - part.second.beg);

					for(auto const& link: std::get<document_link_map>(section_info))
						replace_all(text, "](#" + link.first + ")", "](S-" + link.second + ".md#" + link.first + ")");

					auto filepath = cfg.output_dir + path_separator() + "S-" + part.second.filename + ".md";

					if(!(std::ofstream(filepath) << text))
						throw_errno(part.second.filename);
				}
			}

			if(cfg.outputs.count(output_type::items))
			{
				con_out("Outputting individual items:");

				auto item_info = extract_document_items(doc, section_info);

				for(auto const& part: std::get<document_part_map>(item_info))
				{
					if(cfg.verbose)
						con_out("creating: " << part.second.filename);

					auto text = doc.substr(part.second.beg, part.second.end - part.second.beg);

					for(auto const& link: std::get<document_link_map>(item_info))
						replace_all(text, "](#" + link.first + ")", "](I-" + link.second + ".md#" + link.first + ")");

					auto filepath = cfg.output_dir + path_separator() + "I-" + part.second.filename + ".md";

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
