#ifndef D3Serve_logger_h
#define D3Serve_logger_h

#include <string>

class Logger {
public:
    static void Info(std::string fmt, ...);
    static void Error(std::string fmt, ...);
    static void Debug(std::string fmt, ...);
    static void Trace(std::string fmt, ...);
private:
    static void StdOut(std::string type, std::string fmt, va_list args);
};

#endif
