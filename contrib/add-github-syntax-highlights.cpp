/*
 * add-github-syntax-highlights.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: galik
 */

#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

#define con_out(m) do{std::cout << m << '\n';}while(0)
#define con_err(m) do{std::cerr << m << '\n';}while(0)

#define throw_runtime(m) do{std::ostringstream o;o<<m;throw std::runtime_error(o.str());}while(0)
#define throw_errno(m) throw_runtime(m << ": " << std::strerror(errno))

int usage(std::string prog, int error_code = EXIT_SUCCESS);

void process_markdown(std::istream& is, std::ostream& os);

int main(int, char** argv)
{
	try
	{
		std::string i_file_name;
		std::string o_file_name;

		for(auto arg = argv + 1; *arg; ++arg)
		{
			if(!std::strcmp(*arg, "-h") || !std::strcmp(*arg, "--help"))
				return usage(argv[0]);
			else
			{
				// not a recognized option, treat it like a file name
				if(i_file_name.empty())
					i_file_name = *arg;
				else if(o_file_name.empty())
					o_file_name = *arg;
				else // there should only be a maximum of 2 file names
				{
					con_err("Unknown parameter: " << *arg);
					return usage(argv[0], EXIT_FAILURE);
				}
			}
		}

		// if an input filename was given try to open a file for it
		std::ifstream ifs;
		if(!i_file_name.empty())
			ifs.open(i_file_name);

		// a filename was given and it failed to open
		if(!ifs)
			throw_errno("error: " << i_file_name);

		// if an output filename was given try to open a file for it
		std::ofstream ofs;
		if(!o_file_name.empty())
			ifs.open(o_file_name);

		// a filename was given and it failed to open
		if(!ofs)
			throw_errno("error: " << o_file_name);

		// only use the files if they are open, otherwise use the standard streams
		process_markdown(ifs.is_open() ? ifs : std::cin, ofs.is_open() ? ofs : std::cout);
	}
	catch(std::exception const& e)
	{
		con_err(e.what());
		return EXIT_FAILURE;
	}
	catch(...)
	{
		con_err("Unknown exception.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int usage(std::string prog, int error_code)
{
	if(auto pos = prog.rfind('/') + 1)
		prog.erase(0, pos);

	con_out("");
	con_out("Usage: " << prog << " [OPTIONS] [<input> [<output>]]");
	con_out("");
	con_out("                If no input file <input> is specified");
	con_out("                  the input is taken from the standard input.");
	con_out("");
	con_out("                If no output file <output> is specified");
	con_out("                  the output is sent to the standard output.");
	con_out("");
	con_out("OPTIONS");
	con_out("");
	con_out(" -h|--help    - Print this help massage.");
	con_out("");

	return error_code;
}

class line_ender
{
public:
	line_ender() {}
	line_ender(line_ender const&) = delete;
	line_ender& operator=(line_ender const&) = delete;

private:
	char const* eol = "";

	friend std::ostream& operator<<(std::ostream& o, line_ender& le)
	{
		o << le.eol;
		le.eol = "\n";
		return o;
	}
};

void process_markdown(std::istream& is, std::ostream& os)
{
	line_ender eol;
	bool indented = false;

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
}

