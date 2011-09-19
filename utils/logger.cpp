#include <iostream>
#include <time.h>
#include <string>
#include "logger.h"

#define LOG_FUNCTION(log_type) \
    va_list args;\
    va_start(args, fmt);\
    StdOut(log_type, fmt, args);\
    va_end(args);

void Logger::Info(std::string fmt, ...) {
    LOG_FUNCTION("INFO");
}
void Logger::Error(std::string fmt, ...) {
    LOG_FUNCTION("ERROR");
}
void Logger::Debug(std::string fmt, ...) {
    LOG_FUNCTION("TRACE");
}
void Logger::Trace(std::string fmt, ...) {
    LOG_FUNCTION("TRACE");
}

void Logger::StdOut(std::string type, std::string fmt, va_list args) {
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char time_string[25];
    memcpy(time_string, asctime(timeinfo), 24);
    time_string[24] = '\0';
    printf("[%s] %s | ", time_string, type.c_str());
    vprintf(fmt.c_str(), args);
    printf("\n");
}