#include "loggingService.h"

logger::logger(string file) {
    init(file);
}

void logger::init(string file)
{
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

void logger::log(string message, loglevel level)
{
    loglevel current_level;
    if (console_level == "DEBUG")
        current_level = loglevel::DEBUG;
    if (console_level == "INFO")
        current_level = loglevel::INFO;
    if (console_level == "WARNING")
        current_level = loglevel::WARNING;
    if (console_level == "ERROR")
        current_level = loglevel::ERROR;

    if (level >= current_level) {

        src::severity_logger<loglevel> slg;
        BOOST_LOG_SEV(slg, level) << message;
    }
}