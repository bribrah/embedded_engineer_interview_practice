#pragma once
#include <stdarg.h>
#include <string>

enum LOGLEVEL
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR,
    LOG_NONE
};

class DebugLogger
{

public:
    DebugLogger(LOGLEVEL level);
    DebugLogger();
    void setLogLevel(LOGLEVEL level);

    void info(const char *fmt, ...);
    void error(const char *fmt, ...);
    void debug(const char *fmt, ...);

private:
    std::string formatStr(const char *fmt, va_list args);
    LOGLEVEL logLevel;
};