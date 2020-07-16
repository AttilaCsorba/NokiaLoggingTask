#include "logger_service.h"


int main(int, char* [])
{
    config conf;
    logger_service logger(conf);
    logger.log("Hello", loglevel::WARNING);
    logger.log("valami", loglevel::DEBUG);
    logger.log("some", loglevel::ERROR);
    
    return 0;
}