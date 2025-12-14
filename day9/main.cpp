#include <algorithm>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#include "util.h"


long computeArea(std::pair<long, long>& pt1, std::pair<long, long>& pt2)
{
    long x_delta = abs(pt2.first - pt1.first) + 1;
    long y_delta = abs(pt2.second - pt1.second) + 1;
    return x_delta * y_delta;
}

/*----------------------------------------------------------*/
int main(int argc, char** argv) {
    
    std::cout << "===================================\r\n";
    std::cout << "==========  DAY 9, 2025  ==========\r\n";
    std::cout << "========== MOVIE THEATER ==========\r\n";
    std::cout << "===================================\r\n";


    std::ifstream fin;

    if (argc < 2) {
        std::cout << "Need to supply a file path. Exiting...\r\n";
        return -1;
    }

    if (!file_exists(argv[1])) {
        std::cout << "File " << argv[1] << " does not exist. Exiting...\r\n";
        return -2;
    }

    int CONN_COUNT = 10;
    if (argc > 2) {
        CONN_COUNT = atoi(argv[2]);
    }

    std::cout << "Reading-in data...\r\n";
    fin.open(argv[1], std::ifstream::in);

    std::vector<std::string> lines;
    parseInput(lines, fin);

    fin.close();

    long pt1_ans = 0;
    long pt2_ans = 0;

    std::vector<std::pair<long, long>> points;

    for (auto line = lines.begin(); line != lines.end(); line++) 
    {
        std::vector<std::string> parts = split(*line, ',');
        long x = atol(parts[0].c_str());
        long y = atol(parts[1].c_str());
        points.push_back(std::make_pair(x, y));
    }

    for (auto pt = points.begin(); pt != points.end(); pt++)
    {
        for (auto pt2 = pt + 1; pt2 != points.end(); pt2++)
        {
            long area = computeArea(*pt, *pt2);
            if (area > pt1_ans)
            {
                pt1_ans = area;
            }
        }
    }

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}