#include "day03.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <iomanip>
#include <ios>
#include <sstream>

#include <experimental/optional>
#include <experimental/set>
#include <numeric>
#include <iterator>


typedef enum {
    Up,
    Down,
    Left,
    Right
} Direction;

std::ostream & operator <<(std::ostream &os, Direction& d)
{
    char c;
    switch (d) {
    case Direction::Up:
        c = 'U';
        break;
    case Direction::Down:
        c = 'D';
        break;
    case Direction::Left:
        c = 'L';
        break;
    case Direction::Right:
        c = 'R';
        break;
    }
    os << c;
    return os;
}

typedef struct Move 
{
    Direction direction;
    int distance;
} Move;

typedef std::vector<Move> Route;

std::ostream & operator <<(std::ostream &os, Move& move)
{
    os << move.direction << move.distance << ',' ;
    return os;
}

std::ostream & operator <<(std::ostream &os, Route& route)
{
    for ( auto m : route)
    {
        os << m;
    }
    return os;
}

typedef struct Point 
{
    int x;
    int y;
} Point;

typedef std::vector<Point> Points;

std::ostream & operator <<(std::ostream &os, Point& p)
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
std::ostream & operator <<(std::ostream &os, Points& points)
{
    for ( auto p : points)
    {
        os << p;
    }
    return os;
}

typedef struct Wire 
{
    Route route;
    Points points;
} Wire;

typedef std::vector<Wire> Wires;

std::ostream & operator <<(std::ostream &os, Wire& wire)
{
    os << wire.route << std::endl;
    os << wire.points << std::endl;
    return os;
}

std::ostream & operator <<(std::ostream &os, Wires& wires)
{
    for ( auto w : wires)
    {
        os << w << std::endl;
    }
    return os;
}

static Route parse_input(const std::string& value)
{

    std::istringstream stream(value);
    Route route;

    for(;;)
    {
        if (stream.eof())
        {
            break;
        }

        char c;
        int d;

        stream  >> c
                >> d
            ;

        Move move;
        move.distance = d;

        switch (c) {
        case 'U':
            move.direction = Direction::Up;
            break;
        case 'D':
            move.direction = Direction::Down;
            break;
        case 'L':
            move.direction = Direction::Left;
            break;
        case 'R':
            move.direction = Direction::Right;
            break;
        }
        route.push_back(move);

        stream  >> c;    //comma

    }

    return route;
 }

Points route_points(const Route& route)
{
    Points points;

    Point current = {0,0};
    points.push_back(current);  //start at the origin

    for( auto m : route)
    {
        for (int i = 0; i < m.distance; i++)
        {
            switch (m.direction) {
            case Direction::Up:
                ++current.y;
                break;
            case Direction::Down:
                --current.y;
                break;
            case Direction::Left:
                --current.x;
                break;
            case Direction::Right:
                ++current.x;
                break;
            }
            points.push_back(current);
        }

    }

    return points;
}

static Wires read_file(const std::string& filename)
{
    Wires wires;
    
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return wires;
    }

    std::string line;
    while (std::getline(datafile, line))
    {
        Wire wire;
        wire.route = parse_input(line);
        wire.points = route_points(wire.route);
        wires.push_back(wire);
    }

    return wires;
}

int day03(const std::string& datafile)
{

    auto wires = read_file(datafile);
    if (wires.size()==0)
    {
        std::cout << "No wires in file." << std::ends;
        std::exit(1);
    }

    std::cout << "wires: " << wires.size() << std::endl;
    for (auto w : wires)
    {
        std::cout << "wire points: " << w.points.size() << std::endl;
    }

    return 0;

}
