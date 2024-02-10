#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>
#include <algorithm>

std::vector<std::string> splitString(std::string s, char delim);
std::string toLower(std::string str);
void trimWhiteSpace(std::string &s);