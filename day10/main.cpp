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

class Button
{
private:
    std::vector<int> m_toggle;
public:
    Button(std::vector<int>& lights);
    void press(std::string& init);
    ~Button();
};

Button::Button(std::vector<int>& lights)
{
    m_toggle = lights;
}

/**
 * Toggle lights on/off in the init string according to the indices for this 
 * button, provided at time of creation.
 */
void Button::press(std::string& init)
{
    for (auto i = m_toggle.begin(); i != m_toggle.end(); i++)
    {
        if (init[*i] == '.') {
            init[*i] = '#';
        } else {
            init[*i] = '.';
        }
    }
}

Button::~Button() { }

/*----------------------------------------------------------*/
class ButtonCombo
{
private:
    std::vector<Button*> m_btns;
public:
    ButtonCombo();
    void addButton(Button* btn);
    bool test(std::string goal_state);
    int size();
    void clear();
    ~ButtonCombo();
};

ButtonCombo::ButtonCombo(/* args */)
{
}

int ButtonCombo::size()
{
    return m_btns.size();
}

void ButtonCombo::clear()
{
    m_btns.clear();
}

void ButtonCombo::addButton(Button* btn)
{
    m_btns.push_back(btn);
}


bool ButtonCombo::test(std::string goal_state)
{
    char* state_cstr = (char*)malloc(goal_state.length() + 1);
    state_cstr[goal_state.length()] = '\0';
    memset(state_cstr, '.', goal_state.length());
    std::string state(state_cstr);
    free(state_cstr);
    for (auto btn = m_btns.begin(); btn != m_btns.end(); btn++)
    {
        (*btn)->press(state);
    }

    if (state.compare(goal_state) == 0) 
    {
        return true;
    }

    return false;
}

ButtonCombo::~ButtonCombo()
{
}

/*----------------------------------------------------------*/

void backtrack(std::vector<Button>& btns, std::vector<ButtonCombo>& results, ButtonCombo& curr_combo, int i_start, int n)
{
    if (curr_combo.size() == n)
    {
        results.push_back(curr_combo);
        curr_combo.clear();
        return;
    }

    for (int i = i_start; i < btns.size(); i++)
    {
        ButtonCombo new_curr_combo(curr_combo);
        new_curr_combo.addButton(&btns[i]);
        backtrack(btns, results, new_curr_combo, i + 1, n);
    }
}

void generateButtonCombos(std::vector<Button>& btns, std::vector<ButtonCombo>& results, int n)
{
    ButtonCombo curr_combo;
    backtrack(btns, results, curr_combo, 0, n);
}



/*----------------------------------------------------------*/
int main(int argc, char** argv) {
    
    std::cout << "====================================\r\n";
    std::cout << "==========  DAY 10, 2025  ==========\r\n";
    std::cout << "==========    FACTORY     ==========\r\n";
    std::cout << "====================================\r\n";


    std::ifstream fin;

    if (argc < 2) {
        std::cout << "Need to supply a file path. Exiting...\r\n";
        return -1;
    }

    if (!file_exists(argv[1])) {
        std::cout << "File " << argv[1] << " does not exist. Exiting...\r\n";
        return -2;
    }

    int CONN_COUNT = 10;
    if (argc > 2) {
        CONN_COUNT = atoi(argv[2]);
    }

    std::cout << "Reading-in data...\r\n";
    fin.open(argv[1], std::ifstream::in);

    std::vector<std::string> lines;
    parseInput(lines, fin);

    fin.close();

    long pt1_ans = 0;
    long pt2_ans = 0;

    for (auto line = lines.begin(); line != lines.end(); line++) 
    {
        // std::cout << *line << "\r\n";
        auto parts = split(*line, ' ');
        std::string goal_lights = parts[0].substr(1, parts[0].length() - 2);
        std::cout << "Goal: " << goal_lights << "\r\n";
        std::vector<Button> btns;
        for (int i = 1; i < parts.size() - 1; i++)
        {
            std::vector<int> btn;
            auto numlist = parts[i].substr(1, parts[i].length() - 2);
            auto numstrs = split(numlist, ',');
            for (auto s = numstrs.begin(); s != numstrs.end(); s++)
            {
                btn.push_back(atoi(s->c_str()));
            }
            btns.push_back(Button(btn));
        }

        int n = 0; // number of presses to attempt
        int found_combo = false;
        while (!found_combo && n <= btns.size())
        {
            n++;

            /* attempt all combos of n-many buttons */
            std::cout << "Testing " << n << " button presses... ";
            std::vector<ButtonCombo> combos;
            generateButtonCombos(btns, combos, n);
            std::cout << combos.size() << " combinations...\r\n";
            for (auto combo = combos.begin(); combo != combos.end(); combo++)
            {
                if (combo->test(goal_lights))
                {
                    found_combo = true;
                    break;
                }
            }
        }
        std::cout << " Took " << n << " presses.\r\n";
        pt1_ans += n;
    }


    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}