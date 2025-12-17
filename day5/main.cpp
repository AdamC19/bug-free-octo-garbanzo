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

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::pair;

/*----------------------------------------------------------*/

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

/*
 0 : No overlap
 1 : rng2 starts inside rng1, but ends outside rng1
 2 : rng2 starts inside rng1, and ends inside rng1
*/
int rangeOverlap(pair<long, long>& rnga, pair<long, long>& rngb, pair<long, long>& result)
{
    pair<long, long> rng1; /* rng1 must start before rng2 */
    pair<long, long> rng2;

    if (rnga.first < rngb.first) {
        rng1.first = rnga.first;
        rng1.second = rnga.second;
        rng2.first = rngb.first;
        rng2.second = rngb.second;
    }
    else
    {
        rng1.first = rngb.first;
        rng1.second = rngb.second;
        rng2.first = rnga.first;
        rng2.second = rnga.second;
    }

    if (rng1.second < rng2.first) {
        return 0; /* no overlap */
    }

    if (rng2.first <= rng1.second && rng2.second >= rng1.second) 
    {
        /* range 2 starts within range 1, ends outside range 1 */
        result.first = rng1.first;
        result.second = rng2.second;
        return 1;
    }

    if (rng2.first >= rng1.first && rng2.second <= rng1.second)
    {
        /* range 2 starts within range 1 and ends within range 1 */
        result.first = rng1.first;
        result.second = rng1.second;
        return 2;
    }

    return 0;
}


vector<pair<long, long>> consolidateRanges(vector<pair<long, long>>& rngs) 
{
    vector<pair<long, long>> retval;
    for (auto rng = rngs.begin(); rng != rngs.end(); rng++)
    {
        bool found_overlap = false;
        for (auto check = retval.begin(); check != retval.end(); check++)
        {
            pair<long, long> new_range;
            int overlap = rangeOverlap(*rng, *check, new_range);
            if (overlap == 0) {
                /* no overlap detected */
                continue;
            }
            /* add no new valid ranges, but modify check to hold new bounds */
            found_overlap = true;
            check->first = new_range.first;
            check->second = new_range.second;
            break;
        }

        if (!found_overlap){
            retval.push_back(*rng);
        }
    }
    
    return retval;

}

vector<pair<long, long>> boilDownRanges(vector<pair<long, long>>& rngs) 
{
    vector<pair<long, long>> last_ranges = rngs;
    vector<pair<long, long>> retval = rngs;
    do {
        last_ranges = retval;
        retval = consolidateRanges(last_ranges);
    } while (retval.size() < last_ranges.size());

    return retval;
}


int main(int argc, char** argv) {
    
    std::cout << "===================================\r\n";
    std::cout << "==========  DAY 5, 2025  ==========\r\n";
    std::cout << "==========   CAFETERIA   ==========\r\n";
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

    vector<pair<long, long>> final_ranges = boilDownRanges(ranges);
    // vector<pair<long, long>> check_ranges = ranges;
    // while (final_ranges.size() < check_ranges.size())
    // {
    //     final_ranges = consolidateRanges(check_ranges);
    // }
    
    for (auto rng = final_ranges.begin(); rng != final_ranges.end(); rng++)
    {
        cout << rng->first << "-" << rng->second << endl;
        pt2_ans += (rng->second + 1) - rng->first;
    }

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}