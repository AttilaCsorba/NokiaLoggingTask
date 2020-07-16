#pragma once
#include <string>
#include <fstream>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>
#include "loglevel.h"

using namespace std;

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
const string g_format = "[%TimeStamp%] ID: [%ID%] Severity: (%Severity%) Message: %Message%";
class logger
{
public:
    void init(string file) {
        boost::log::add_common_attributes();
        boost::shared_ptr< logging::core > core = logging::core::get();
        core->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
        core->add_global_attribute("ID", attrs::counter< unsigned int >(1));
        boost::log::register_simple_formatter_factory< loglevel, char >("Severity");
        logging::add_console_log(std::cout, boost::log::keywords::format = g_format);

        /*logging::add_file_log
        (
            keywords::file_name = file + ".txt",
            keywords::target_file_name = file + "%N.txt",
            keywords::rotation_size = 10 * 1024 * 1024,
            keywords::max_files = 10,
            keywords::format = g_format
        );*/
    }

	logger(string file) {
        init(file);
	}

    void log(string message, loglevel level)
    {
        src::severity_logger<loglevel> slg;
        BOOST_LOG_SEV(slg,level) << message;
    }
};

