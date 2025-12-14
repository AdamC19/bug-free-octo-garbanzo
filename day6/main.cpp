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
    std::cout << "========== DAY 6, 2025 ==========\r\n";
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

    std::vector<std::vector<long>> rows;

    auto line = lines.begin();
    for(; line != lines.end() - 1; line++)
    {
        std::vector<std::string> gubbins = split(*line, ' ');
        std::vector<long> row;

        for (auto gub = gubbins.begin(); gub != gubbins.end(); gub++)
        {
            if (gub->length() >= 1)
            {
                row.push_back(atol(gub->c_str()));
            }
        }
        rows.push_back(row);
    }

    std::vector<char> ops;
    std::vector<std::string> gubbins = split(*line, ' ');
    for (auto gub = gubbins.begin(); gub != gubbins.end(); gub++)
    {
        if (gub->length() >= 1)
        {
            ops.push_back(gub->at(0));
        }
    }

    std::vector<long> answers;
    for (int i_col = 0; i_col < rows[0].size(); i_col++)
    {
        
        long answer = rows[0][i_col];
        for (int i_row = 1; i_row < rows.size(); i_row++)
        {
            if (ops[i_col] == '+')
            {
                answer += rows[i_row][i_col];
            }
            else if (ops[i_col] == '*')
            {
                answer = answer * rows[i_row][i_col];
            }
        }
        answers.push_back(answer);
        pt1_ans += answer;
    }

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}