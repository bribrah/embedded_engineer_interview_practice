#pragma once

#include <map>
#include <vector>
#include <string>
#include "util.h"
#include "DebugLogger.h"
#include <tuple>
#include <cstring>

typedef int (*CommandPtr)(char *argv[], int argc);

class CommandParser
{
public:
    CommandParser();

    int registerNewCommand(std::string commandName, CommandPtr commandFunction);
    int parseCommandString(std::string command);

private:
    std::map<std::string, CommandPtr> commands;
    DebugLogger log;
};