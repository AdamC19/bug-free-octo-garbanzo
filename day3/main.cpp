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
    std::cout << "========== DAY 3, 2025 ==========\r\n";
    std::cout << "==========    LOBBY    ==========\r\n";
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

        int i = 0;
        char num2[13] = {0};
        memset(num2, '\0', 13);
        int i_start = 0;
        while (strlen(num2) < DIGITS)
        {
            /* find highest valued digit */
            int stop_at = line->length() - (DIGITS - strlen(num2));
            int i_of_max = -1;
            int max_dig = 0;
            for (int ii = i_start; ii <= stop_at; ii++)
            {
                int dig = line->at(ii) - 48;
                if (dig > max_dig)
                {
                    max_dig = dig;
                    i_of_max = ii;
                }
            }
            i_start = i_of_max + 1;
            num2[i] = line->at(i_of_max);
            i++;
        }
        long max_pt2 = atol(num2);
        pt2_ans += max_pt2;
        std::cout << "Max for line PART 2 = " << max_pt2 << "\r\n";
    }



    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}