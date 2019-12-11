#include "day08.h"
#include "day08_lib.h"

#include "stream_helpers.h"

// #include <cstdlib>
#include <fstream>
#include <iostream>
// #include <string>
#include <vector>
// #include <map>

// #include <iostream>
#include <iomanip>
// #include <ios>
// #include <sstream>

// #include <optional>
// #include <experimental/set>
// #include <numeric>
// #include <iterator>
// #include <limits>
#include <algorithm>

int count_character(const char c, const std::string& s)
{
    return std::count(s.begin(), s.end(), c);
}

int day08(const std::string& filename)
{

    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return 1;
    }

    int pixel_width(25);
    int pixel_height(6);

    std::vector<std::string> layers;

     int min_layer = (INT_MAX);;
    int min_layer_count(INT_MAX);
    
    for (;;)
    {
        std::string layer;
        datafile >> std::setw(pixel_height*pixel_width) >> layer;
        if (datafile.eof())
        {
            break;
        }

        layers.push_back(layer);

        int count = count_character( '0', layer);
        if (count < min_layer_count)
        {
            min_layer_count = count;
            min_layer = layers.size()-1;
        }

    }

    std::cout << "layers size=" << layers.size() << std::endl
              << "layer= " << min_layer << std::endl
              << "check count: " << count_character('1', layers.at(min_layer)) * count_character('2', layers.at(min_layer))
              << std::endl    
            ;


    return -1;
}
