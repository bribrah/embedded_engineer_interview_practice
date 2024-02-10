#include "DebugLogger.h"
#include <cstdio>
#include <iostream>

const char *LOGLEVEL_NAMES[] = {
    "LOG_DEBUG",
    "LOG_INFO",
    "LOG_ERROR",
    "LOG_NONE",
};

DebugLogger::DebugLogger(LOGLEVEL level)
{
    this->logLevel = level;
}

DebugLogger::DebugLogger()
{
    this->logLevel = LOG_INFO;
}

std::string DebugLogger::formatStr(const char *fmt, va_list args)
{
    char buf[1024];
    int len;
    len = vsnprintf(buf, sizeof(buf), fmt, args);
    return std::string(buf, len);
}

void DebugLogger::setLogLevel(LOGLEVEL level)
{
    logLevel = level;
}

void DebugLogger::info(const char *fmt, ...)
{
    if (logLevel > LOG_INFO)
    {
        return;
    }
    va_list args;
    va_start(args, fmt);
    std::string fmted = formatStr(fmt, args);
    va_end(args);
    std::cout << "LOG_INFO :: " << fmted << std::endl;
}

void DebugLogger::error(const char *fmt, ...)
{
    if (logLevel > LOG_ERROR)
    {
        return;
    }
    va_list args;
    va_start(args, fmt);
    std::string fmted = formatStr(fmt, args);
    va_end(args);
    std::cout << "LOG_ERROR :: " << fmted << std::endl;
}

void DebugLogger::debug(const char *fmt, ...)
{
    if (logLevel > LOG_DEBUG)
    {
        return;
    }
    va_list args;
    va_start(args, fmt);
    std::string fmted = formatStr(fmt, args);
    va_end(args);
    std::cout << "LOG_DEBUG :: " << fmted << std::endl;
}