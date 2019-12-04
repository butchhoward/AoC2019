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


std::ostream & operator <<(std::ostream &os, std::vector<int>& intcode)
{
    for ( auto m : intcode)
    {
        os << m << "," ;
    }
    return os;
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


std::vector<int> read_file_02(const std::string& filename)
{
    std::vector<int> intcode;
    
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return intcode;
    }

    for (;;)
    {
        int code = 0;
        datafile >> code;
        if (datafile.eof())
        {
            break;
        }
        intcode.push_back(code);
        char comma = ',';
        datafile >> comma;
        if (datafile.eof())
        {
            break;
        }
    }


    return intcode;
}

void run_code( std::vector<int>& intcode )
{
    for(std::vector<int>::size_type i = 0; i < intcode.size();)
    {
        switch (intcode.at(i))
        {
            case 1:
            {
                auto a = intcode.at(intcode.at(i+1));
                auto b = intcode.at(intcode.at(i+2));
                auto d = intcode.at(i+3);
                //std::cout << "add " << a << " " << b << " " << d << std::endl;
                intcode.at(d) = a + b;
                i += 4;
            }
                break;
            case 2:
            {
                auto a = intcode.at(intcode.at(i+1));
                auto b = intcode.at(intcode.at(i+2));
                auto d = intcode.at(i+3);
                //std::cout << "mul " << a << " " << b << " " << d << std::endl;
                intcode.at(d) = a * b;
                i += 4;
            }
                break;
            default:
                return;
        }
    }
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

int day02(const std::string& datafile)
{
    auto intcode = read_file_02(datafile);
    if (intcode.size()==0)
    {
        std::cout << "No codes in file." << std::ends;
        std::exit(1);
    }

    std::cout << intcode << std::endl;
    run_code(intcode);
    std::cout << "---" << std::endl << intcode << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Need a file name" << std::endl;
        std::exit(1);
    }

    int day(0);
    std::istringstream stream(argv[1]);
    stream >> day;
    std::string datafile(argv[2]);
    std::cout << day << std::endl << datafile << std::endl;

    switch (day) {
    case 1:
        day01(datafile);
        break;
    case 2:
        day02(datafile);
        break;
    }

    return 0;
}
