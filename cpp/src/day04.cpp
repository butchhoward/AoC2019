#include "day04.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include <sstream>
#include <string>

bool has_run_of_digits(const std::string& scode)
{

    for (std::string::size_type i = 1; i < scode.length(); i++)
    {
        if ( scode[i-1] == scode[i])
        {
            return true;
        }
    }
    return false;
}

bool digits_increase_left_to_right(const std::string& scode)
{

    for (std::string::size_type i = 1; i < scode.length(); i++)
    {
        if ( scode[i-1] <= scode[i])
        {
            return true;
        }
    }

    return false;
}

bool is_possible_passcode(int code)
{
    std::stringstream str_code;
    str_code << code;

    std::string scode = str_code.str();

    if (scode.length() == 6 &&
        has_run_of_digits(scode) &&
        digits_increase_left_to_right(scode)
       )
    {
        return true;
    }

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
int day04(const std::string& range_definition)
{
    //254032,789860
    std::istringstream stream(range_definition);


    char c;
    int begin, end;

    stream  >> begin
            >> c        //comma
            >> end;
            ;



    std::cout << count_possible_passcodes(begin, end);

    return 0;
}
