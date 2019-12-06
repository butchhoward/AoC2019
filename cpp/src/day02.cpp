#include "day02.h"
#include "int_code.h"

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


void day02_part1(const std::vector<int> intcode_orig)
{
    std::vector<int> intcode = intcode_orig;

    intcode[1] = 12;
    intcode[2] = 2;

    //std::cout << intcode << std::endl;
    run_code(intcode);
    //std::cout << "---" << std::endl << intcode << std::endl;
    std::cout << "day02 part 1: " << intcode[0] << std::endl;
}

void day02_part2(const std::vector<int> intcode_orig)
{

    for (int noun = 0;noun < 100; noun++)
    {
        for (int verb = 0;verb < 100; verb++)
        {
            std::vector<int> intcode = intcode_orig;

            intcode[1] = noun;
            intcode[2] = verb;

            run_code(intcode);

            if (intcode[0] == 19690720)
            {
                std::cout << "day02 part 2: " << noun * 100 + verb << std::endl;
                return;
            }
        }
    }
    std::cout << "day02 part 2: no match" << std::endl;
}

int day02(const std::string& datafile)
{
    auto intcode = read_file(datafile);
    if (intcode.size()==0)
    {
        std::cout << "No codes in file." << std::ends;
        std::exit(1);
    }

    day02_part1(intcode);
    day02_part2(intcode);

    return 0;
}
