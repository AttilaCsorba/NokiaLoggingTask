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
#include "config.h"
#include <map> 

using namespace std;

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
class logger_service
{

private:
    config conf;
    int lineid;
    map<int, string> errlist;
    map<int, string>::iterator itr;
public:
    void getErrors();

    void clear(int id);

    void init();

    logger_service();

    void log(string message, loglevel level);
};

