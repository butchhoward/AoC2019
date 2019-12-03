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


typedef enum {
    Sleep,
    Wake,
    Other
} EventType;

typedef struct Module 
{
    int mass;
    int fuel;
} Module;

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


Module parse_input(const std::string& value)
{
// 123456

    std::istringstream stream(value);
    Module item = {0,0};
    
    stream >> item.mass;

    return item;
 }

auto calculate_fuel(const int mass)
{
    return  (mass /3) - 2;
}

std::vector<Module> read_file(const std::string& filename)
{
    std::vector<Module> modules;
    
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening output file" << std::endl;
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
        auto module = parse_input(line);
        module.fuel = calculate_fuel(module.mass);
        modules.push_back(module);
    }

    return modules;
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Need a file name" << std::endl;
        std::exit(1);
    }

    auto modules = read_file(argv[1]);
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
