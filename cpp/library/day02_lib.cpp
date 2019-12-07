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


int day02_part1(const std::vector<int> intcode_orig)
{
    std::vector<int> intcode = intcode_orig;

    intcode[1] = 12;
    intcode[2] = 2;

    run_code(intcode);
    return intcode[0];
}

int day02_part2(const std::vector<int> intcode_orig)
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
                return noun * 100 + verb;
            }
        }
    }
    return -1;
}
