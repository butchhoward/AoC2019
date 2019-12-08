#include "day05.h"
#include "day05_lib.h"

#include "int_code.h"
#include "stream_helpers.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <iomanip>
#include <ios>
#include <sstream>

#include <experimental/optional>
#include <experimental/set>
#include <numeric>
#include <iterator>
#include <limits>


int day05(const std::string& filename)
{
    //254032,789860
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return 1;
    }

    Storage intcode;
    std::string intcode_string;
    std::getline(datafile, intcode_string);
    std::istringstream stream(intcode_string);

    for(;;)
    {
        if (stream.eof())
        {
            break;
        }

        char c;
        int code;

        stream  >> code
                >> c        //comma
                ;

        intcode.push_back(code);
    }

    Storage input = {1}, output;
    run_code(intcode, input, output);
    std::cout << "day05 " << output << std::endl;

    return 0;
}

