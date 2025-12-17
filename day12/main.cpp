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

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

/*----------------------------------------------------------*/


class PresentPattern
{
private:
    vector<vector<char>> m_pattern;
public:
    PresentPattern(vector<string> pattern);
    ~PresentPattern();
};

PresentPattern::PresentPattern(vector<string> pattern)
{
    for (auto str = pattern.begin(); str != pattern.end(); str++)
    {
        vector<char> row;
        for (auto c = str->begin(); c != str->end(); c++)
        {
            row.push_back(*c);
        }
        m_pattern.push_back(row);
    }
}

PresentPattern::~PresentPattern(){}


/*----------------------------------------------------------*/


class Region
{
private:
    int m_size_x;
    int m_size_y;
    char** m_canvas;
public:
    Region(int size_x, int size_y);
    ~Region();
};

Region::Region(int size_x, int size_y)
{
    m_canvas = (char**)malloc(sizeof(char**) * size_y);
    for (int y = 0; y < size_y; y++)
    {
        m_canvas[y] = (char*)malloc(size_x);
        memset(m_canvas[y], '.', size_x);
    }
}

Region::~Region()
{
    for (int i = 0; i < m_size_y; i++)
    {
        free(m_canvas[i]);
    }
    free(m_canvas);
}


/*----------------------------------------------------------*/
int main(int argc, char** argv) {
    
    cout << "====================================\r\n";
    cout << "==========  DAY 12, 2025  ==========\r\n";
    cout << "========== XMAS TREE FARM ==========\r\n";
    cout << "====================================\r\n";


    std::ifstream fin;

    if (argc < 2) {
        cout << "Need to supply a file path. Exiting...\r\n";
        return -1;
    }

    if (!file_exists(argv[1])) {
        cout << "File " << argv[1] << " does not exist. Exiting...\r\n";
        return -2;
    }

    int CONN_COUNT = 10;
    if (argc > 2) {
        CONN_COUNT = atoi(argv[2]);
    }

    cout << "Reading-in data...\r\n";
    fin.open(argv[1], std::ifstream::in);

    vector<string> lines;
    parseInput(lines, fin);

    fin.close();

    long pt1_ans = 0;
    long pt2_ans = 0;

    auto line = lines.begin();

    for (auto line = lines.begin(); line != lines.end(); line++) 
    {
        
    }

    cout << "PART 1 ANSWER: " << pt1_ans << endl;
    cout << "PART 2 ANSWER: " << pt2_ans << endl;

    return 0;
}