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



/*----------------------------------------------------------*/
int main(int argc, char** argv) {
    
    std::cout << "====================================\r\n";
    std::cout << "==========  DAY 10, 2025  ==========\r\n";
    std::cout << "==========    FACTORY     ==========\r\n";
    std::cout << "====================================\r\n";


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

    for (auto line = lines.begin(); line != lines.end(); line++) 
    {
        auto parts = split(*line, ' ');
    }


    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}