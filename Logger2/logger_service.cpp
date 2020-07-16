#include "logger_service.h"
#include <iostream> 
#include <iterator> 


logger_service::logger_service() {
    conf.init();
    init();
    ctr = 1;
}

void logger_service::init()
{
    boost::log::add_common_attributes();
    boost::shared_ptr< logging::core > core = logging::core::get();
    core->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
    core->add_global_attribute("ID", attrs::counter< unsigned int >(1));
    boost::log::register_simple_formatter_factory< loglevel, char >("Severity");
    if(conf.getconsole_logging())
        logging::add_console_log(std::cout, boost::log::keywords::format = conf.getconsole_format());

    if (conf.getfile_logging()) {
        logging::add_file_log
        (
            keywords::file_name = conf.getfile_name() + ".txt",
            keywords::target_file_name = conf.getfile_name() + "%N.txt",
            keywords::rotation_size = conf.getfile_full() * 1024 * 1024,
            keywords::max_files = conf.getfile_max() ,
            keywords::format = conf.getfile_format()
        );
    }
}

void logger_service::log(string message, loglevel level)
{
    /*string console_level = conf.getconsole_level();
    loglevel curr_level;
    if (console_level == "DEBUG")
        curr_level = loglevel::DEBUG;
    else if (console_level == "INFO")
        curr_level = loglevel::INFO;
    else if (console_level == "WARNING")
        curr_level = loglevel::WARNING;
    else if (console_level == "ERROR")
        curr_level = loglevel::ERROR;*/

    if (level = loglevel::ERROR) {
        errlist.insert(pair<int, string>(ctr, "ERROR"));
    }

   // if (level >= curr_level) {
        src::severity_logger<loglevel> slg;
        BOOST_LOG_SEV(slg, level) << message;
    //}
    ctr++;
}

    void logger_service::getErrors() {
        for (const auto& x : errlist) {
            std::cout << x.first << ": " << x.second << "\n";
        }
    }