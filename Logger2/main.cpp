#include "logger_service.h"


int main(int, char* [])
{
    logger_service logger;
    logger.log("Hello", loglevel::WARNING);
    logger.log("valami", loglevel::DEBUG);
    logger.log("some", loglevel::ERROR);
    logger.getErrors();
    logger.clear(3);
    
    return 0;
}