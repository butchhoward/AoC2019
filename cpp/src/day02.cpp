#include "day02.h"
#include "day02_lib.h"
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



int day02(const std::string& datafile)
{
    auto intcode = read_file(datafile);
    if (intcode.size()==0)
    {
        std::cout << "No codes in file." << std::ends;
        std::exit(1);
    }

    std::cout << "day02 part 1: " << day02_part1(intcode) << std::endl;
    std::cout << "day02 part 2: " << day02_part2(intcode) << std::endl;

    return 0;
}
