#include "logger_service.h"


int main(int, char* [])
{
    logger log1("log");
    log1.log("Hello",loglevel::WARNING);
    
    return 0;
}