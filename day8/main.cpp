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


class Point
{
private:
    int m_x;
    int m_y;
    int m_z;
    int m_id;
public:
    Point(int x, int y, int z, int id);
    ~Point();
    double distance(Point& pt2);
    int getId();
    void print();
};

Point::Point(int x, int y, int z, int id)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_id = id;
}

Point::~Point(){}


double Point::distance(Point& pt2)
{
    float delta_x = 1.0*(pt2.m_x - this->m_x);
    float delta_y = 1.0*(pt2.m_y - this->m_y);
    float delta_z = 1.0*(pt2.m_z - this->m_z);
    return sqrt(pow(delta_x, 2.0) + pow(delta_y, 2.0) + pow(delta_z, 2.0));
}

int Point::getId(){
    return m_id;
}

void Point::print()
{
    printf("%3d", m_id);
    std::cout << " (" << m_x << "," << m_y << "," << m_z << ")";
}


/*----------------------------------------------------------*/
class Connection
{
private:
    Point* m_pt1;
    Point* m_pt2;
public:
    Connection(Point* pt1, Point* pt2);
    double distance();
    void print();
    Point* getPoint(int which);
    ~Connection();
};

Connection::Connection(Point* pt1, Point* pt2)
{
    m_pt1 = pt1;
    m_pt2 = pt2;
}

double Connection::distance()
{
    return m_pt1->distance(*m_pt2);
}

void Connection::print()
{
    m_pt1->print();
    std::cout << "\t--- ";
    m_pt2->print();
    std::cout << "\t= ";
    printf("%.3f", distance());
}


Point* Connection::getPoint(int which) 
{
    if (which == 0)
    {
        return m_pt1;
    }
    return m_pt2;
}

Connection::~Connection() {}

/*----------------------------------------------------------*/
class Circuit
{
private:
    /* data */
    std::vector<Point*> m_boxes;
public:
    Circuit();
    ~Circuit();
    bool hasBox(Point* box);
    void addBox(Point* box);
};

Circuit::Circuit(/* args */)
{
}

Circuit::~Circuit(){}

bool Circuit::hasBox(Point* box)
{
    int box_i = 0;
    while (box_i < m_boxes.size() && box != m_boxes[box_i])
    {
        box_i++;
    }
    if (box_i < m_boxes.size())
    {
        return box == m_boxes[box_i];
    }
    return false;
}

void Circuit::addBox(Point* box)
{
    m_boxes.push_back(box);
}



/*----------------------------------------------------------*/
int main(int argc, char** argv) {
    
    std::cout << "=================================\r\n";
    std::cout << "========== DAY 8, 2025 ==========\r\n";
    std::cout << "========== PLAYGROUND  ==========\r\n";
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

    std::vector<Point> boxes;
    std::vector<Connection> conns;
    std::map<std::pair<int, int>, double> distances;
    std::map<std::pair<int, int>, double> short_dists;

    int id = 0;
    for (auto line = lines.begin(); line != lines.end(); line++) 
    {
        std::vector<std::string> parts = split(*line, ',');
        boxes.push_back(Point(atoi(parts[0].c_str()), atoi(parts[1].c_str()), atoi(parts[2].c_str()), id));
        id++;
    }

    std::cout << "Computing distances...\r\n";
    for (int i = 0; i < boxes.size(); i++) 
    {
        for (int ii = i + 1; ii < boxes.size(); ii++) 
        {
            Connection conn(&boxes[i], &boxes[ii]);
            conns.push_back(conn);

            // double dist = boxes[i].distance(boxes[ii]);
            // if (short_dists.size() < CONN_COUNT)
            // {
            //     short_dists.emplace(std::make_pair(i, ii), dist);
            // }
            // else 
            // {
            //     emplaceIfShort(short_dists, std::make_pair(i, ii), dist);
            // }
            // distances.emplace(std::make_pair(i, ii), dist);
        }
    }
    std::cout << "Computed " << conns.size() << " distances.\r\n";

    std::cout << "Sorting connections list...\r\n";

    std::sort(conns.begin(), conns.end(), [](Connection a, Connection b){
        return a.distance() < b.distance();
    });

    std::cout << "Analyzing the shortest " << CONN_COUNT << " connections...\r\n";

    std::vector<std::vector<Point*>> circuits;
    
    std::cout << "\r\nConstructing circuits...\r\n";
    for (int i = 0; i < CONN_COUNT; i++)
    {
        Point* pt1 = conns[i].getPoint(0);
        Point* pt2 = conns[i].getPoint(1);
        
        bool found = false;

        /* determine if either of the boxes are in an existing circuit */
        for (auto cir = circuits.begin(); cir != circuits.end(); cir++)
        {
            auto it1 = std::find(cir->begin(), cir->end(), pt1);
            auto it2 = std::find(cir->begin(), cir->end(), pt2);
            if (it1 != cir->end() && it2 == cir->end()) 
            {
                cir->push_back(pt2);
                found = true;
                break;
            }
            else if (it2 != cir->end() && it1 == cir->end())
            {
                cir->push_back(pt1);
                found = true;
                break;
            }
        }

        if (circuits.size() == 0 || !found)
        {
            std::vector<Point*> new_cir;
            new_cir.push_back(pt1);
            new_cir.push_back(pt2);
            circuits.push_back(new_cir);
        }
    }
    
    std::cout << "Constructed " << circuits.size() << " circuits.\r\n";

    std::cout << "PART 1 ANSWER: " << pt1_ans << std::endl;
    std::cout << "PART 2 ANSWER: " << pt2_ans << std::endl;

    return 0;
}