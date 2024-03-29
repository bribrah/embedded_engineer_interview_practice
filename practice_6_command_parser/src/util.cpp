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

std::string toLower(std::string str)
{
    std::string res = str;

    for (char &c : res)
    {
        c = std::tolower(c);
    }
    return res;
}

void trimWhiteSpace(std::string &s)
{
    // front
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));

    // back
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}