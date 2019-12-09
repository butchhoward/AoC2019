#include "day07.h"
#include "day07_lib.h"
#include "int_code.h"

#include "stream_helpers.h"

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

#include <optional>
#include <experimental/set>
#include <numeric>
#include <iterator>
#include <limits>


int day07(const std::string& datafile)
{
    int_code::Storage intcode = int_code::read_file(datafile);
    if (intcode.empty())
    {
        std::cerr << "invalid data file" << std::endl;
        return -1;
    }

    auto t = day07lib::find_optimum_amplifier_setting(intcode);
    std::cout << "Day7 part amplifier settings: " << t.first << " | " << t.second << std::endl;

    return -1;
}
