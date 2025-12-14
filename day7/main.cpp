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


int computeBeams(std::vector<std::vector<char>>& diagram, int i_row) 
{
    std::vector<int> beam_locs;
    int retval = 0;

    if (i_row - 1 < 0) {
        return retval;
    }

    /* locate beams coming down from previous row */
    for(int x = 0; x < diagram[i_row - 1].size(); x++)
    {
        if (diagram[i_row - 1][x] == '|' || diagram[i_row - 1][x] == 'S')
        {
            beam_locs.push_back(x);
        }
    }

    for (auto x_loc = beam_locs.begin(); x_loc != beam_locs.end(); x_loc++) 
    {
        if (diagram[i_row][*x_loc] == '^') 
        {
            /* beam splits */
            retval++;
            if (*x_loc > 0) 
            {
                diagram[i_row][*x_loc - 1] = '|';
            }

            if (*x_loc < diagram[i_row].size() - 1)
            {
                diagram[i_row][*x_loc + 1] = '|';
            }
        } 
        else
        {
            diagram[i_row][*x_loc] = '|';
        }
    }

    return retval;
}


int main(int argc, char** argv) {
    
    std::cout << "=================================\r\n";
    std::cout << "========== DAY 7, 2025 ==========\r\n";
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

    std::vector<std::vector<char>> diagram;

    for (auto line = lines.begin(); line != lines.end(); line++) 
    {
        std::vector<char> row;
        for (auto c = line->begin(); c != line->end(); c++)
        {
            row.push_back(*c);
        }
        diagram.push_back(row);
    }

    for (int i = 1; i < diagram.size(); i++)
    {
        pt1_ans += computeBeams(diagram, i);
    }

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}