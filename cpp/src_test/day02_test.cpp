
#include "day02_test.h"
#include "day02_lib.h"
#include "int_code.h"
#include "stream_helpers.h"

#include <iostream>

static bool test(std::vector<int>& v, const std::vector<int>& r)
{
    //std::cout << v << std::endl;
    run_code(v);
    //std::cout << v << std::endl;
    std::vector<int>::const_iterator a, b;
    for (  a = v.begin(), b = r.begin(); a != v.end(); a++, b++)
    {
        if ( *a != *b )
        {
            return false;
        }
    }
    return true;
}

bool day02_unit_test()
{
    {
        std::vector<int> v = {1,9,10,3,2,3,11,0,99,30,40,50};
        std::vector<int> r = {3500,9,10,70,2,3,11,0,99,30,40,50};
        if (!test( v, r ))
        {
            std::cout << " Fail 1 " << std::endl << v << std::endl << r << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {1,0,0,0,99};
        std::vector<int> r = {2,0,0,0,99};
        if (!test( v, r ))
        {
            std::cout << " Fail 2 " << std::endl << v << std::endl << r << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {2,3,0,3,99};
        std::vector<int> r = {2,3,0,6,99};
        if (!test( v, r ))
        {
            std::cout << " Fail 3 " << std::endl << v << std::endl << r << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {2,4,4,5,99,0};
        std::vector<int> r = {2,4,4,5,99,9801};
        if (!test( v, r ))
        {
            std::cout << " Fail 4 " << std::endl << v << std::endl << r << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {1,1,1,4,99,5,6,0,99};
        std::vector<int> r = {30,1,1,4,2,5,6,0,99};
        if (!test( v, r ))
        {
            std::cout << " Fail 5 " << std::endl << v << std::endl << r << std::endl;
            return false;
        }
    }

    // 1,0,0,0,99 becomes 2,0,0,0,99 (1 + 1 = 2).
    // 2,3,0,3,99 becomes 2,3,0,6,99 (3 * 2 = 6).
    // 2,4,4,5,99,0 becomes 2,4,4,5,99,9801 (99 * 99 = 9801).
    //1,1,1,4,99,5,6,0,99 becomes 30,1,1,4,2,5,6,0,99.
    return true;
}

bool day02_test()
{
    std::vector<int> v1 = {1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,9,1,19,1,19,5,23,1,23,5,27,2,27,10,31,1,31,9,35,1,35,5,39,1,6,39,43,2,9,43,47,1,5,47,51,2,6,51,55,1,5,55,59,2,10,59,63,1,63,6,67,2,67,6,71,2,10,71,75,1,6,75,79,2,79,9,83,1,83,5,87,1,87,9,91,1,91,9,95,1,10,95,99,1,99,13,103,2,6,103,107,1,107,5,111,1,6,111,115,1,9,115,119,1,119,9,123,2,123,10,127,1,6,127,131,2,131,13,135,1,13,135,139,1,9,139,143,1,9,143,147,1,147,13,151,1,151,9,155,1,155,13,159,1,6,159,163,1,13,163,167,1,2,167,171,1,171,13,0,99,2,0,14,0};

    if ( 3654868 != day02_part1(v1))
    {
        std::cout << "FAILED: day02_part1() << std::endl";
        return false;
    }

    if ( 7014 != day02_part2(v1))
    {
        std::cout << "FAILED: day02_part2() << std::endl";
        return false;
    }

    std::cout << "PASSED Day 2" << std::endl;
    return true;
}
