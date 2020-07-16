#include "logger_service.h"

int main(int, char* [])
{
    logger_service logger;
    logger.log("test1", loglevel::WARNING);
    logger.log("test2", loglevel::ERROR);
    logger.log("test3", loglevel::ERROR);
    logger.getErrors();
    logger.clear(3);
    logger.getErrors();
    logger.clear(0);
    logger.getErrors();
    
    return 0;
}