#include "logger_service.h"


int main(int, char* [])
{
    config c;
    logger_service logger(c);
    logger.log("Hello", loglevel::WARNING);
    logger.log("valami", loglevel::DEBUG);
    logger.log("some", loglevel::ERROR);
    
    return 0;
}