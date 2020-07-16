#include "logger_service.h"


logger_service::logger_service() {
    conf.init();
    init();
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
        string file = conf.getfile_name();
        int rotationsize = conf.getfile_full();
        int maxfiles = conf.getfile_max();
        logging::add_file_log
        (
            keywords::file_name = file + ".txt",
            keywords::target_file_name = file + "%N.txt",
            keywords::rotation_size = rotationsize * 1024 * 1024,
            keywords::max_files = maxfiles,
            keywords::format = conf.getfile_format()
        );
    }
}

void logger_service::log(string message, loglevel level)
{
    string console_level = conf.getconsole_level();
    loglevel current_level1;
    if (console_level == "DEBUG")
        current_level1 = loglevel::DEBUG;
    else if (console_level == "INFO")
        current_level1 = loglevel::INFO;
    else if (console_level == "WARNING")
        current_level1 = loglevel::WARNING;
    else if (console_level == "ERROR")
        current_level1 = loglevel::ERROR;

    if (level >= current_level1) {
        src::severity_logger<loglevel> slg;
       BOOST_LOG_SEV(slg, level) << message;
    }
}