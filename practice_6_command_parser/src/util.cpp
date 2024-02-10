#include "util.h"

std::vector<std::string> splitString(std::string s, char delim)
{
    using namespace std;
    vector<string> strings;
    istringstream f(s);
    while (getline(f, s, delim))
    {
        strings.push_back(s);
    }
    return strings;
}