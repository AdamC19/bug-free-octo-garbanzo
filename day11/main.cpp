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

int findViablePaths(map<string, vector<string>>& nodes, string node_name)
{
    // cout << "Attempting to lookup " << node_name << " node...\r\n";

    /* loop in previous call has located the "out" node. Return 1 */
    if (node_name.compare("out") == 0) {
        return 1;
    }

    auto node = nodes.find(node_name);
    if (node == nodes.end()) {
        /* node name doesn't exist for some reason. Dead end, so return 0 */
        return 0;
    }

    int retval = 0;
    for (auto opt = node->second.begin(); opt != node->second.end(); opt++)
    {
        
        retval += findViablePaths(nodes, *opt);
    }
    return retval;
}

/*----------------------------------------------------------*/

void enumViablePaths(map<string, vector<string>>& nodes, string node_name, vector<vector<string>>& paths, vector<string>& curr_path)
{
    /* loop in previous call has located the "out" node. Return 1 */
    if (node_name.compare("out") == 0) {
        // curr_path.push_back("out"); // function has already done this
        paths.push_back(curr_path);
        curr_path.clear();
        return;
    }

    auto node = nodes.find(node_name);
    if (node == nodes.end()) {
        /* node name doesn't exist for some reason. Dead end, so return here */
        return;
    }
    
    for (auto opt = node->second.begin(); opt != node->second.end(); opt++)
    {
        vector<string> new_path(curr_path);
        new_path.push_back(*opt);
        enumViablePaths(nodes, *opt, paths, new_path);
    }
    return;
}

/*----------------------------------------------------------*/
int main(int argc, char** argv) {
    
    cout << "====================================\r\n";
    cout << "==========  DAY 11, 2025  ==========\r\n";
    cout << "==========    REACTOR     ==========\r\n";
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

    
    map<string, vector<string>> devices;

    for (auto line = lines.begin(); line != lines.end(); line++) 
    {
        auto parts = split(*line, ' ');
        string dev_name = parts[0].substr(0, 3);
        vector<string> opts;
        for (int i = 1; i < parts.size(); i++)
        {
            opts.push_back(parts[i]);
        }
        devices.emplace(dev_name, opts);
    }
    cout << ">>> Beginning PART 1 analysis... ";
    string start_str("you");
    pt1_ans = findViablePaths(devices, start_str);
    cout << "Done.\r\n\r\n";

    cout << ">>> Beginning PART 2 analysis... \r\n";
    vector<string> start_path;
    string pt2_start("svr");
    start_path.push_back(pt2_start);
    vector<vector<string>> paths;
    cout << "Enumerating paths... \r\n";
    enumViablePaths(devices, pt2_start, paths, start_path);
    cout << "Done.\r\n";

    cout << "Checking every path... ";
    for (auto path = paths.begin(); path != paths.end(); path++)
    {
        bool found_dac = false;
        bool found_fft = false;
        for (auto str = path->begin(); str != path->end(); str++)
        {
            cout << *str;
            if (str + 1 != path->end()){
                cout << ",";
            }
            
            if (str->compare("dac") == 0)
            {
                found_dac = true;
            }
            if (str->compare("fft") == 0)
            {
                found_fft = true;
            }
        }
        cout << " | ";
        if (found_dac && found_fft)
        {
            cout << "FOUND!!!\r\n";
            pt2_ans++;
        } else {
            cout << "NOT found...\r\n";
        }
    }
    cout << "Done.\r\n";

    cout << "PART 1 ANSWER: " << pt1_ans << endl;
    cout << "PART 2 ANSWER: " << pt2_ans << endl;

    return 0;
}