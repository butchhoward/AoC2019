#include "day06_lib.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <iostream>
#include <iomanip>
#include <ios>
#include <sstream>

#include <experimental/optional>
#include <experimental/set>
#include <numeric>
#include <iterator>
#include <limits>

using namespace day06lib;

std::ostream & operator <<(std::ostream &os, std::vector<std::string>& ss)
{
    for ( auto s : ss)
    {
        os << s << "," ;
    }
    return os;
}

std::ostream & day06lib::operator<<(std::ostream &os, day06lib::OrbitItem& orbititem)
{
    // not sure why the stream helper for vector<string> is having trouble here, but I'll sort it later

    os << orbititem.name << " | " 
       << orbititem.orbiting << " | "
       ;
    for ( auto s : orbititem.orbitals)
    {
        os << s << "," ;
    }

    os   
        << std::endl
       ;
    return os;
}

// std::ostream & day06lib::operator<<(std::ostream &os, day06lib::OrbitItem& orbititem)
// {
//     // not sure why the stream helper for vector<string> is having trouble here, but I'll sort it later

//     os << orbititem.name << " | " 
//        << orbititem.orbiting << " | "
//        << orbititem.orbitals
//        ;
//     return os;
// }


std::ostream & day06lib::operator<<(std::ostream &os, day06lib::Universe& universe)
{
    for ( auto orbititem : universe)
    {
        os << orbititem.second;
    }
    return os;
}

void day06lib::add_to_universe(day06lib::Universe &universe, std::string orbited, std::string orbiter)
{
    auto being_orbited = universe.find(orbited);    
    if (being_orbited == universe.end())
    {
        day06lib::OrbitItem orbititem;
        orbititem.name = orbited;
        orbititem.orbitals.push_back(orbiter);
        universe.insert({orbited, orbititem});
    }
    else
    {
        being_orbited->second.orbitals.push_back(orbiter);
    }

    auto inorbit = universe.find(orbiter);
    if (inorbit == universe.end())
    {
        day06lib::OrbitItem orbititem;
        orbititem.name = orbiter;
        orbititem.orbiting = orbited;
        universe.insert({orbiter, orbititem});
    }
    else
    {
        if (inorbit->second.orbiting.empty())
        {
            inorbit->second.orbiting = orbited;
        }
        else if (inorbit->second.orbiting != orbited)
        {
            std::cerr << "add_to_universe using existing orbiter which aready orbiting somewhere else: "
                      << orbited << ")" << orbiter << std::endl;
        }
    }
}

day06lib::Universe day06lib::read_file(const std::string& filename)
{
    day06lib::Universe universe;
    
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cerr << "Error opening input file" << std::endl;
        return universe;
    }

    std::string line;
    while (std::getline(datafile, line))
    {
        std::string::size_type pos = line.find(')');
        if (pos != std::string::npos)
        {
            std::string orbited, orbiter;
            orbited = line.substr(0, pos);
            orbiter = line.substr(pos+1);

            add_to_universe( universe, orbited, orbiter);
        }
    }

    return universe;
}

int count_orbits_from_item(const day06lib::Universe& universe, const day06lib::OrbitItem& item, int depth)
{
    int count(depth);
    for (auto& orbital : item.orbitals)
    {
        auto it = universe.find(orbital);
        if (it == universe.end())
        {
            std::cerr << "unable to find '" << orbital << "' in the universe" << std::endl;
            break;
        }

        count += count_orbits_from_item(universe, it->second, depth+1);
    }
    return count;
}

int day06lib::count_orbits(const day06lib::Universe& universe)
{
    (void)universe;

    //could also find the only one that is not orbiting something (assuming that assumption holds)
    auto comit = universe.find("COM");
    if (comit == universe.end())
    {
        return 0;
    }

    auto& com = comit->second;
    return count_orbits_from_item(universe, com, 0);
}

std::pair<std::string, int> day06lib::find_common_orbiting_node(const day06lib::Universe& universe, const std::string& source, const std::string& destination)
{
    int transfers(0);

    auto it = universe.find(source);
    auto orbiting = it->second.orbiting;

    while (!day06lib::item_reachable_from(universe, orbiting, destination))
    {
        if (it == universe.end() ||
            it->second.orbiting.empty())
        {
            transfers = -1;
            orbiting.clear();
            break;
        }

        ++transfers;
        it = universe.find(orbiting);
        orbiting = it->second.orbiting;
    }

    return std::make_pair(orbiting, transfers);
}

int day06lib::count_transfers_outbound(const day06lib::Universe& universe, const std::string& source, const std::string& destination)
{

    int transfers(0);

    auto it = universe.find(source);
    for (auto orbital : it->second.orbitals)
    { 
        if (orbital == destination)
        {
            break;
        }

        if (day06lib::item_reachable_from(universe, orbital, destination))
        {
            ++transfers;
            transfers += count_transfers_outbound(universe, orbital, destination);
            break;
        }
    }

    return transfers;

}

int day06lib::minimum_transfers_between(const day06lib::Universe& universe, const std::string& source, const std::string& destination)
{

    if (source == destination)
    {
        return 0;
    }

    //into the gravity well until we find a node that can reach the destination
    auto common = find_common_orbiting_node(universe, source, destination);
    if (common.second == -1)
    {
        return 0;
    }

    int transfers_outbound = count_transfers_outbound(universe, common.first, destination);
    return common.second + transfers_outbound;
}

bool day06lib::item_reachable_from(const day06lib::Universe& universe, const std::string& com, const std::string& destination)
{
    auto it = universe.find(com);
    if (it == universe.end() ||
        it->second.orbitals.empty())
    {
        return false;
    }

    bool can_reach(false);
    for (auto& orbital : it->second.orbitals)
    {
        if (orbital == destination)
        {
            can_reach = true;
            break;
        }

        can_reach = day06lib::item_reachable_from(universe, orbital, destination);
        if (can_reach)
        {
            break;
        }
    }


    return can_reach;
}
