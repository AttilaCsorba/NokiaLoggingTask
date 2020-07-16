#pragma once
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "loglevel.h"
#include "Constants.h"

using namespace std;
namespace po = boost::program_options;

class config
{
private:
	void read_settings(po::options_description& desc,
		po::variables_map& vm);
	void init();
	void trace();
	bool console_logging;
	string console_format;
	string console_level;
	bool file_logging;
	string file_name;
	bool rotation;
	int file_full;
	int file_max;
	string file_format;
	string file_level;
public:
	config();
	bool getconsole_logging() { return console_logging; };
	string getconsole_format() { return console_format; };
	string getconsole_level() { return console_level; };
	bool getfile_logging() { return file_logging; };
	string getfile_name() { return file_name; };
	bool getrotation() { return rotation; };
	int getfile_full() { return file_full; };
	int getfile_max() { return file_max; };
	string getfile_format() { return file_format; };
	string getfile_level() { return file_level; };
};

