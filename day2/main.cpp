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

    std::vector<std::string> ranges = split(lines[0], ',');


    long pt1_ans = 0;
    long pt2_ans = 0;

    for (auto rng = ranges.begin(); rng != ranges.end(); rng++)
    {
        std::vector<std::string> parts = split(*rng, '-');
        long start = atol(parts[0].c_str());
        long end = atol(parts[1].c_str());
        
        std::cout << "Analyzing range " << start << " - " << end << "...\r\n";
        
        for(long n = start; n <= end; n++) 
        {
            std::stringstream ss;
            ss << n;
            std::string nstr = ss.str();
            int len = nstr.length();
            // if (len % 2 != 0)
            // {
            //     continue;
            // }
            const char* nchars = nstr.c_str();
            int half_len = len / 2;

            if (memcmp(nchars, nchars + half_len, half_len) == 0)
            {
                std::cout << "  " << n << "\r\n";
                pt1_ans += n;
            }

            for (int slice = half_len; slice > 0; slice--)
            {
                if (strlen(nchars) % slice == 0)
                {
                    bool match = true;
                    int offset = 0;
                    while (match && offset < len - slice) 
                    {
                        if (memcmp(nchars + offset, nchars + offset + slice, slice) != 0)
                        {
                            match = false;
                        }
                        offset += slice;
                    }
                    if (match) 
                    {
                        std::cout << "    " << n << "\r\n";
                        pt2_ans += n;
                        break; // no need to analyze other slices if this one works
                    }
                }
            }
        }
    }

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}