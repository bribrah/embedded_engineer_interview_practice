#include "CommandParser.h"

CommandParser::CommandParser() {}

int CommandParser::registerNewCommand(std::string commandName, CommandPtr commandFunc)
{
    int status;
    std::vector<std::string> split = splitString(commandName, ' ');
    if (split.size() > 1)
    {
        log.error("Command name needs to be 1 word, got %d words", split.size());
        return -1;
    }

    commands.emplace(toLower(commandName), commandFunc);
    return 0;
}

int CommandParser::parseCommandString(std::string fullStr)
{
    int status;

    std::vector<std::string> split = splitString(fullStr, ' ');
    int length = split.size();
    if (length == 0)
    {
        return -1;
    }
    std::string command = toLower(split[0]);

    if (commands.find(command) != commands.end())
    {
        CommandPtr thisCommand = commands[command];
        if (length > 1)
        {
            char **argv = new char *[length - 1];
            for (int i = 1; i < length; i++)
            {
                argv[i - 1] = new char[split[i].length() + 1];
                std::strcpy(argv[i - 1], split[i].c_str());
            }
            thisCommand(argv, length - 1);
            for (int i = 0; i < length - 1; i++)
            {
                delete argv[i];
            }
            delete[] argv;
        }
        else
        {
            thisCommand(nullptr, 0);
        }
    }
    else
    {
        log.error("Could not find command %s", command.c_str());
    }
    return 0;
}
