#include "day04.h"

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

bool has_run_of_digits(const std::string& scode)
{

    int adjacent_same_count(0);
    for (std::string::size_type i = 1; i < scode.length(); i++)
    {
        if ( scode[i-1] == scode[i])
        {
            ++adjacent_same_count;
        }
    }
    // std::cout << "adj: " << adjacent_same_count << " ";
    return adjacent_same_count > 0;
}

bool digits_increase_left_to_right(const std::string& scode)
{

    for (std::string::size_type i = 1; i < scode.length(); i++)
    {
        if ( scode[i-1] > scode[i] )
        {
            // std::cout << "incr: " << scode[i-1] << ">=" << scode[i] << " ";
            return false;
        }
    }

    return true;
}

bool is_possible_passcode(int code)
{
    std::stringstream str_code;
    str_code << code;

    std::string scode = str_code.str();

    // std::cout << "|" << scode << "| ";

    if (scode.length() == 6 &&
        has_run_of_digits(scode) &&
        digits_increase_left_to_right(scode)
       )
    {
        // std::cout << "passcode" << std::endl;
        return true;
    }
    // std::cout << "not" << std::endl;

    return false;
}
int count_possible_passcodes(int begin, int end)
{
    int count(0);

    for (int i = begin; i <= end; i++)
    {
        if (is_possible_passcode(i))
        {
            ++count;
        }
    }

    return count;
}
int day04(const std::string& filename)
{
    //254032,789860
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return 1;
    }

    std::string range_text;
    while(std::getline(datafile, range_text))
    {
        std::istringstream stream(range_text);

        char c;
        int begin, end;

        stream  >> begin
                >> c        //comma
                >> end;
                ;



        std::cout << count_possible_passcodes(begin, end) << std::endl;
    }
    return 0;
}
