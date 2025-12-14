
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <cstdio>

#include "util.h"

/**
 * Read lines from ifstream fin and push them into the lines vector
 */
int parseInput(std::vector<std::string> &lines, std::ifstream& fin) {
    while (!fin.eof()) {
        std::string s;
        std::getline(fin, s);
        lines.push_back(s);
    }
    return lines.size();
}

/**
 * Split the src string at delim into a vector of strings
 */
std::vector<std::string> split(std::string src, char delim) {
    std::vector<std::string> retval;
    std::stringstream ss(src);
    std::string tmp;

    while(std::getline(ss, tmp, delim)) {
        if (tmp.length() > 0)
            retval.push_back(tmp);
    }
    return retval;
}

/**
 * Read lines from fin, split them at delim, and parse to integers.
 */
std::vector<std::vector<int>> parseSplit(std::vector<std::string> &lines, std::ifstream& fin, char delim) {
    std::vector<std::vector<int>> retval;
    parseInput(lines, fin);
    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
        std::vector<std::string> parts = split(*it, delim);
        std::vector<int> line;
        for(std::vector<std::string>::iterator part = parts.begin(); part != parts.end(); ++part) {
            line.push_back(atoi((*part).c_str()));
        }
        retval.push_back(line);
    }

    return retval;
}


std::string stripWhitespace(std::string src) 
{
    std::string retval;
    bool leading = true;
    int i_start = 0;
    for (int i = 0; i < src.length(); i++) 
    {
        char c = src[i];
        if (leading) 
        {
            if (c != ' ' && c != '\n' && c != '\r' && c != '\t') 
            {
                i_start = i;
                break;
            }
        }
    }

    int i_end = src.length() - 1;
    for (int i = src.length() - 1; i > i_start; i--) 
    {
        char c = src[i];
        if (c != ' ' && c != '\n' && c != '\r' && c != '\t') 
        {
            i_end = i;
            break;
        }
    }

    for (int i = i_start; i <= i_end; i++) 
    {
        retval.push_back(src[i]);
    }
    
    return retval;
}