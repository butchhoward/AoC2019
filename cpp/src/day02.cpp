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

#include <optional>
#include <experimental/set>
#include <numeric>
#include <iterator>


int day02(const std::string& datafile)
{
    auto intcode = int_code::read_file(datafile);
    if (intcode.size()==0)
    {
        std::cout << "No codes in file." << std::ends;
        std::exit(1);
    }

    std::cout << "day02 part 1: " << day02_part1(intcode) << std::endl;
    std::cout << "day02 part 2: " << day02_part2(intcode) << std::endl;

    return 0;
}
