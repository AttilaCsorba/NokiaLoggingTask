#include "loggingService.h"


int main(int, char* [])
{
    logger log1("log");
    log1.log("Hello",loglevel::ERROR);

    return 0;
}