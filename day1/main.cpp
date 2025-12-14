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
    std::cout << "========== DAY 1, 2025 ==========\r\n";
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

    int DIAL_TICKS = 100;
    int dial = 50;
    int pt1_ans = 0;
    int pt2_ans = 0;

    for (auto line = lines.begin(); line != lines.end(); line++)
    {
        const char* txt = line->c_str();

        int sign = 0;
        if (txt[0] == 'L')
        {
            sign = -1;
        }
        else if (txt[0] == 'R')
        {
            sign = 1;
        }
        else
        {
            continue;
        }

        int num = atoi(txt + 1);
        std::cout << "Rotating " << num << "... ";
        int delta = sign * num;
        int clicks = 0;
        int zero_crosses = 0;
        std::cout << "dial = " << dial << ". ";

        while(clicks < abs(delta))
        {
            if (dial == 0)
            {
                zero_crosses++;
            }
            dial += sign;
            if (dial < 0)
            {
                dial += DIAL_TICKS;
            }
            else if (dial >= DIAL_TICKS)
            {
                dial -= DIAL_TICKS;
            }
            clicks++;
        }
        
        // while (dial < 0)
        // {
        //     // std::cout << "fixing(+)... ";
        //     dial += DIAL_TICKS;
        // }
        // while (dial >= DIAL_TICKS)
        // {
        //     // std::cout << "fixing(-)... ";
        //     dial -= DIAL_TICKS;
        // }

        std::cout << "Crossed 0 " << zero_crosses << " times. ";
        pt2_ans += zero_crosses;

        std::cout << "Dial is actually at " << dial << "\r\n";
        if (dial == 0)
        {
            pt1_ans++;
        }
    }

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}