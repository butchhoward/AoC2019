#include "day03_test.h"


#include <iostream>
#include <vector>

std::ostream & operator <<(std::ostream &os, std::vector<int>& intcode)
{
    for ( auto m : intcode)
    {
        os << m << "," ;
    }
    return os;
}

void run_code( std::vector<int>& intcode )
{
    for(std::vector<int>::size_type i = 0; i < intcode.size();)
    {
        switch (intcode.at(i))
        {
            case 1:
            {
                auto a = intcode.at(intcode.at(i+1));
                auto b = intcode.at(intcode.at(i+2));
                auto d = intcode.at(i+3);
                //std::cout << "add " << a << " " << b << " " << d << std::endl;
                intcode.at(d) = a + b;
                i += 4;
            }
                break;
            case 2:
            {
                auto a = intcode.at(intcode.at(i+1));
                auto b = intcode.at(intcode.at(i+2));
                auto d = intcode.at(i+3);
                //std::cout << "mul " << a << " " << b << " " << d << std::endl;
                intcode.at(d) = a * b;
                i += 4;
            }
                break;
            default:
                return;
        }
    }
}

bool test(std::vector<int>& v, const std::vector<int>& r)
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

bool day02_test()
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

int main()
{
    day02_test();
    day03_test();
    return 0;
}
