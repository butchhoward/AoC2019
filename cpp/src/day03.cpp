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

#include <optional>
#include <experimental/set>
#include <numeric>
#include <iterator>
#include <limits>


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
    int x,y;
    bool operator==(const Point& p) const
        { return p.x == this->x && p.y == this->y;}
    bool operator!=(const Point& p) const
        { return !(p == *this);}
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

int manhattan_distance( const Point& p1, const Point& p2)
{
    //For example, in the plane, the taxicab distance between (p1,p2) and (q1,q2) is |p1-q1|+|p2-q2|.
    return abs(p1.x-p2.x) + abs(p1.y-p2.y);
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

Points find_intersections( const Wire& wire1, const Wire& wire2)
{
    Points intersections;

    for (auto p1 : wire1.points)
    {
        auto it = std::find_if( wire2.points.begin(), wire2.points.end(),
                                [p1](const Point& p2){return p1 == p2;}
                                );
        if (it != wire2.points.end())
        {
            intersections.push_back(*it);
        }
    }

    return intersections;

}

int find_closest_intersection_to_origin(const Points& intersections)
{
    Point origin = {0,0};
    Point nearest = origin;
    int current_nearest_m = INT_MAX;
    for (auto p : intersections)
    {
        // std::cout << "I: " << p << " D: " << manhattan_distance(origin, p) << std::endl;

        if ( p == origin)
        {
            continue;
        }
        if (manhattan_distance(origin, p) < current_nearest_m)
        {
            nearest = p;
            current_nearest_m = manhattan_distance(origin, p);
        }
    }
    // std::cout << "Nearest intersection: " << nearest << std::endl;

    return current_nearest_m;
}

typedef struct IntersectionSteps 
{
    Point intersection;
    int steps;
} IntersectionSteps;

std::ostream & operator <<(std::ostream &os, IntersectionSteps& i)
{
    os << i.intersection << i.steps << ',' ;
    return os;
}


std::vector<IntersectionSteps> get_steps_to_intersections(const Route& route, const Points& intersections)
{
    //re-route the paths, saving the steps to each intersection 
    std::vector<IntersectionSteps> isteps;

    Point current = {0,0};
    int current_steps(0);

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

            ++current_steps;

            auto found = std::find(intersections.begin(), intersections.end(), current);
            if ( found != intersections.end())
            {
                IntersectionSteps istep = {current, current_steps};
                isteps.push_back(istep);
            }
        }

    }

    return isteps;
}

int find_fastest_intersection(const Wires& wires, const Points& intersections)
{
    std::vector< std::vector<IntersectionSteps> > route_steps;
    for (auto w : wires)
    {
        std::vector<IntersectionSteps> isteps = get_steps_to_intersections(w.route, intersections);
        route_steps.push_back(isteps);
    }


    int fastest = INT_MAX;
    for (auto s0 : route_steps.at(0) )
    {
        auto it = std::find_if(route_steps.at(1).begin(), route_steps.at(1).end(), 
                        [s0] (const IntersectionSteps& s) { return s.intersection == s0.intersection; });
        IntersectionSteps s1 = *it;

        // std::cout << s0.intersection << s0.steps << " " 
        //           << s1.intersection << s1.steps << " " 
        //           ;

        int s = s0.steps + s1.steps;
        if (s < fastest)
        {
            fastest = s;
        }
        // std::cout << s << ", ";
    }
    // std::cout << std::endl;

    return fastest;

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
    if (wires.size() < 2)
    {
        std::cout << wires.size() << " wire in file. Not enough to work with." << std::ends;
        std::exit(1);
    }

    // std::cout << "wires: " << wires.size() << std::endl;
    // for (auto w : wires)
    // {
    //     std::cout << "wire points: " << w.points.size() << std::endl;
    //     std::cout << w.points << std::endl;
    // }

    Points intersections = find_intersections(wires.at(0), wires.at(1));
    // std::cout << intersections << std::endl;


    std::cout << "Nearest Distance: " << find_closest_intersection_to_origin(intersections) << std::endl;


    //part2
    std::cout << "Fastest: " << find_fastest_intersection(wires, intersections) << std::endl;

    return 0;

}
