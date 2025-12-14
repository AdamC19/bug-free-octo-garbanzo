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

bool canAccessSquare(std::vector<std::vector<char>>& stuff, int x, int y)
{
    
    int rolls = 0;
    if (x > 0 && stuff[y][x - 1] != '.') {rolls++;}
    if (x > 0 && y > 0 && stuff[y - 1][x - 1] != '.') {rolls++;}
    if (x > 0 && y < stuff.size() - 1 && stuff[y + 1][x - 1] != '.') {rolls++;}

    if (y > 0 && stuff[y - 1][x] != '.') {rolls++;}
    if (y < stuff.size() - 1 && stuff[y + 1][x] != '.') {rolls++;}

    if (x < stuff[y].size() - 1 && stuff[y][x + 1] != '.') {rolls++;}
    if (x < stuff[y].size() - 1 && y > 0 && stuff[y - 1][x + 1] != '.') {rolls++;}
    if (x < stuff[y].size() - 1 && y < stuff.size() - 1 && stuff[y + 1][x + 1] != '.') {rolls++;}

    return rolls < 4;
}


int markRemovableRolls(std::vector<std::vector<char>>& stuff, char mark)
{
    int retval = 0;
    for (int y = 0; y < stuff.size(); y++)
    {
        for(int x = 0; x < stuff[y].size(); x++)
        {
            if (stuff[y][x] == '.')
            {
                continue;
            }
            if (canAccessSquare(stuff, x, y))
            {
                retval++;
                stuff[y][x] = mark;
            }
        }
    }
    return retval;
}


int removeRolls(std::vector<std::vector<char>>& stuff, char removeChar) 
{
    int retval = 0;
    for (int y = 0; y < stuff.size(); y++)
    {
        for(int x = 0; x < stuff[y].size(); x++)
        {
            if (stuff[y][x] == removeChar)
            {
                retval++;
                stuff[y][x] = '.';
            }
        }
    }
    return retval;
}

int main(int argc, char** argv) {
    
    std::cout << "=================================\r\n";
    std::cout << "========== DAY 4, 2025 ==========\r\n";
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

    std::vector<std::vector<char>> stuff;

    for(auto line = lines.begin(); line != lines.end(); line++)
    {
        std::vector<char> row;
        for (auto c = line->begin(); c != line->end(); c++)
        {
            row.push_back(*c);
        }
        stuff.push_back(row);
    }


    for (int y = 0; y < stuff.size(); y++)
    {
        for(int x = 0; x < stuff[y].size(); x++)
        {
            if (stuff[y][x] == '.')
            {
                continue;
            }

            if (canAccessSquare(stuff, x, y))
            {
                // stuff[y][x] = 'x';
                pt1_ans++;
            }
        }
    }

    /* PART 2 */
    int rolls_removed = 0;
    int rounds = 0;
    do 
    {
        rolls_removed = markRemovableRolls(stuff, 'x');
        std::cout << "Round " << rounds << ": Removable rolls = " << rolls_removed;
        rolls_removed = removeRolls(stuff, 'x');
        std::cout << ". Removed " << rolls_removed << " rolls\r\n";
        pt2_ans += rolls_removed;
        rounds++;
    } while (rolls_removed > 0);

    std::cout << "Rounds taken to remove all possible rolls: " << rounds << "\r\n";

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}