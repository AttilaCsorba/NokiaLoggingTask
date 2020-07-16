#include "config.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>

const string Constants::settings_file = "settings.ini";

const char Constants::console_logging[16] = "console_logging";
const char Constants::console_format[150] = "console_format";
const char Constants::console_level[16] = "console_level";
const char Constants::file_logging[16] = "file_logging";
const char Constants::file_name[16] = "file_name";
const char Constants::rotation[16] = "rotation";
const char Constants::file_full[16] = "file_full";
const char Constants::file_max[16] = "file_max";
const char Constants::file_format[150] = "file_format";
const char Constants::file_level[16] = "file_level";

namespace po = boost::program_options;

config::config()
{
	init();
	trace();
}

void config::read_settings(po::options_description& desc,
	po::variables_map& vm)
{
	std::ifstream settings_file(Constants::settings_file);

	vm = po::variables_map();

	po::store(po::parse_config_file(settings_file, desc), vm);
	po::notify(vm);
}

void config::init()
{
	po::options_description desc("Options");
	desc.add_options()
		(Constants::console_logging, po::value<bool>(&console_logging), Constants::console_logging)
		(Constants::console_format, po::value<std::string>(&console_format), Constants::console_format)
		(Constants::console_level, po::value<std::string>(&console_level), Constants::console_level)
		(Constants::file_logging, po::value<bool>(&file_logging), Constants::file_logging)
		(Constants::file_name, po::value<std::string>(&console_format), Constants::file_name)
		(Constants::rotation, po::value<bool>(&rotation), Constants::rotation)
		(Constants::file_full, po::value<int>(&file_full), Constants::file_full)
		(Constants::file_max, po::value<int>(&file_max), Constants::file_max)
		(Constants::file_format, po::value<string>(&file_format), Constants::file_format)
		(Constants::file_level, po::value<string>(&file_level), Constants::file_level);
	po::variables_map vm;

	read_settings(desc, vm);

}

void config::trace()
{
	std::cout << "console_logging = " << console_logging << std::endl;
	std::cout << "console_format = " << console_format << std::endl;
	std::cout << "console_level = " << console_level << std::endl;
	std::cout << "file_logging = " << file_logging << std::endl;
	std::cout << "file_name = " << file_name << std::endl;
	std::cout << "rotation = " << rotation << std::endl;
	std::cout << "file_full = " << file_full << std::endl;
	std::cout << "file_max = " << file_max << std::endl;
	std::cout << "file_format = " << file_format << std::endl;
	std::cout << "file_level = " <<file_level << std::endl;

}