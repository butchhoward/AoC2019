#include "day06.h"
#include "day06_lib.h"

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

#include <experimental/optional>
#include <experimental/set>
#include <numeric>
#include <iterator>
#include <limits>

int day06(const std::string& datafile)
{
    day06lib::Universe universe = day06lib::read_file(datafile);

    //std::cout << universe << std::endl << "universe size=" << universe.size() << std::endl;

    std::cout << "Day 6 part 1 Direct and Indirect orbits: " << day06lib::count_orbits(universe) << std::endl;
    std::cout << "Day 6 part 2 Transfers from YOU to SAN: " << day06lib::minimum_transfers_between(universe, "YOU", "SAN") << std::endl;

    return -1;
}
