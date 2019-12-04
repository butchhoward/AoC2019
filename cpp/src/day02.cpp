#include "day02.h"

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



std::ostream & operator <<(std::ostream &os, std::vector<int>& intcode)
{
    for ( auto m : intcode)
    {
        os << m << "," ;
    }
    return os;
}


static std::vector<int> read_file(const std::string& filename)
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

int day02(const std::string& datafile)
{
    auto intcode = read_file(datafile);
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
