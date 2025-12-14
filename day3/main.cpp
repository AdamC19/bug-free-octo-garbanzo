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


int main(int argc, char** argv) {
    
    std::cout << "=================================\r\n";
    std::cout << "========== DAY 2, 2025 ==========\r\n";
    std::cout << "=================================\r\n";


    std::ifstream fin;

    if (argc < 2) {
        std::cout << "Need to supply a file path. Exiting...\r\n";
        return -1;
    }

    if (!file_exists(argv[1])) {
        std::cout << "File " << argv[1] << " does not exist. Exiting...\r\n";
        return -2;
    }

    std::cout << "Reading-in data...\r\n";
    fin.open(argv[1], std::ifstream::in);

    std::vector<std::string> lines;
    parseInput(lines, fin);

    fin.close();

    long pt1_ans = 0;
    long pt2_ans = 0;

    int DIGITS = 12;

    for(auto line = lines.begin(); line != lines.end(); line++)
    {
        auto c1 = line->begin();
        char numstr[3] = {0};
        int max = 0;
        while (c1 != line->end())
        {
            for (auto c2 = c1 + 1; c2 != line->end(); c2++) 
            {
                numstr[0] = *c1;
                numstr[1] = *c2;
                int num = atoi(numstr);
                if (num > max)
                {
                    max = num;
                }
            }
            c1++;
        }
        std::cout << "Max for line = " << max << "\r\n";
        pt1_ans += max;
    }



    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}