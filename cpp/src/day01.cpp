#include "day01.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
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

std::ostream & operator <<(std::ostream &os, const Module& event)
{
    os 
        << "m=" << event.mass
        << " f=" << event.fuel
        ;
    return os;
}

std::ostream & operator <<(std::ostream &os, std::vector<Module>& modules)
{
    for ( auto m : modules)
    {
        os << m << std::endl;
    }
    return os;
}


Module parse_input_01(const std::string& value)
{
// 123456

    std::istringstream stream(value);
    Module item = {0,0};
    
    stream >> item.mass;

    return item;
 }

auto calculate_fuel_for_mass(const int mass)
{
    if ( mass <= 0 )
    {
        return 0;
    }

    auto fuel_mass = (mass / 3) - 2;
    if (fuel_mass < 0 )
    {
        fuel_mass = 0;
    }

    return fuel_mass;
}

auto calculate_fuel(const int mass)
{
    if ( mass <= 0 )
    {
        return 0;
    }
    auto fuel_mass = calculate_fuel_for_mass(mass);

    return fuel_mass + calculate_fuel(fuel_mass);
}


std::vector<Module> read_file_01(const std::string& filename)
{
    std::vector<Module> modules;
    
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return modules;
    }

    std::vector<std::string> raw;
    std::string line;
    while (std::getline(datafile, line))
    {
        raw.push_back(line);
    }

    for ( auto line : raw)
    {
        auto module = parse_input_01(line);
        module.fuel = calculate_fuel(module.mass);
        modules.push_back(module);
    }

    return modules;
}

int day01(const std::string& datafile)
{
    
    auto modules = read_file_01(datafile);
    if (modules.size()==0)
    {
        std::cout << "No modules in file." << std::ends;
        std::exit(1);
    }

    std::cout << modules << std::endl;

    auto total_fuel = std::accumulate(modules.begin(), modules.end(),
                                    0,
                                    [](int a, const Module& item) 
                                        {return a + item.fuel;}
                                    );
    std::cout << "total_fuel=" << total_fuel << std::endl;


    return 0;
}
