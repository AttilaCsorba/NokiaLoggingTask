#include "logger_service.h"
#include <iostream> 
#include <iterator> 

struct MyException : public exception {
    const char* what() const throw () {
        return "id Error";
    }
};

logger_service::logger_service() {
    conf.init();
    init();
    lineid = 1;
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
    string console_level = conf.getconsole_level();
    loglevel cons_level;
    if (console_level == "DEBUG")
        cons_level = loglevel::DEBUG;
    else if (console_level == "INFO")
        cons_level = loglevel::INFO;
    else if (console_level == "WARNING")
        cons_level = loglevel::WARNING;
    else if (console_level == "ERROR")
        cons_level = loglevel::ERROR;

    if (level == loglevel::ERROR) {
        errlist.insert(pair<int, string>(lineid, message));
    }

   if (level >= cons_level) {
        src::severity_logger<loglevel> slg;
        BOOST_LOG_SEV(slg, level) << message;
    }
    lineid++;
}

    void logger_service::getErrors() {
        cout << "\n" << "Listing all errors:\n";
        for (const auto& x : errlist) {
            std::cout << x.first << ": " << x.second << "\n";
        }
    }

    void logger_service::clear(int id) {
        try {
            if (errlist.erase(id) == 0)
                throw MyException();
            else
                cout << "\nError with id: " << id << " has been deleted!\n";
        }
        catch (MyException & e) {
            std::cout << "\nNo error found with this id\n" << std::endl;
            std::cout << e.what() << std::endl;
            loglevel level = loglevel::ERROR;
            src::severity_logger<loglevel> slg;
            BOOST_LOG_SEV(slg, level) << "ID error";
        }
    }