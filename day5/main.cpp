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


long min(long a, long b) 
{
    if (a < b)
        return a;

    return b;
}

long max(long a, long b) 
{
    if (a > b)
        return a;
        
    return b;
}


std::pair<long, long>* findRange(std::vector<std::pair<long, long>>& ranges, long n)
{

    for (auto rng = ranges.begin(); rng != ranges.end(); rng++)
    {
        if (n >= rng->first && n <= rng->second) 
        {
            return &(*rng);
        }
    }
    return NULL;
}


int rangeOverlap(std::pair<long, long>& rng1, std::pair<long, long>& rng2)
{
    if (rng1.second <= rng2.second && rng1.second >= rng1.first) 
    {
        /* range 1 end point is within range 2 */
        return -1;
    }

    if (rng1.first >= rng2.first && rng1.first <= rng2.second)
    {
        /* range 1 start point is within range 2 */
        return 1;
    }

    return 0;
}


std::pair<long, long> consolidateRanges(std::pair<long, long>& rng1, std::pair<long, long>& rng2) 
{
    std::pair<long, long> retval(0, 0);

    if (rangeOverlap(rng1, rng2) != 0)
    {
        long start1 = rng1.first;
        long end1 = rng1.second;
        long start2 = rng2.first;
        long end2 = rng2.second;

        long start = min(start1, start2);
        long end = max(end1, end2);

        retval.first = start;
        retval.second = end;
    }
    return retval;
}


int main(int argc, char** argv) {
    
    std::cout << "=================================\r\n";
    std::cout << "========== DAY 5, 2025 ==========\r\n";
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

    std::vector<std::pair<long, long>> ranges;

    std::cout << "Reading ranges... ";
    auto line = lines.begin();
    for(; line != lines.end(); line++)
    {
        if (line->length() < 1)
        {
            std::cout << "Done.\r\n";
            break;
        }

        std::vector<std::string> parts = split(*line, '-');
        long start = atol(parts[0].c_str());
        long end = atol(parts[1].c_str());
        ranges.push_back(std::make_pair(start, end));
    }

    line++;
    
    std::cout << "Reading IDs...... ";
    for(; line != lines.end(); line++)
    {
        long id = atol(line->c_str());
        std::pair<long, long>* rng = findRange(ranges, id);
        if (rng != NULL)
        {
            // std::cout << id << " is fresh\r\n";
            pt1_ans++;
        }
    }
    std::cout << "Done.\r\n";


    std::cout << "\r\n===== PART 2 =====\r\n";

    std::vector<std::pair<long, long>> fewer_ranges;

    for (auto rng = ranges.begin(); rng != ranges.end(); rng++)
    {
        auto check = rng + 1;
        while (check != ranges.end())
        {
            if (rangeOverlap(*rng, *check)) {
            }
        }
    }

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}