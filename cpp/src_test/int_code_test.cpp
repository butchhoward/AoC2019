
#include "int_code_test.h"
#include "int_code.h"
#include "test_runner.h"

#include "stream_helpers.h"

#include <iostream>

static bool test(std::vector<int>& v, const std::vector<int>& r, Storage& input, Storage& output)
{
    run_code(v, input, output);
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
static bool test(std::vector<int>& v, const std::vector<int>& r)
{
    Storage input;
    Storage output;
    return test(v, r, input, output);
}

bool intcode_outputs_the_input()
{        
    Storage v = {3,0,4,0,99};
    Storage r = {77,0,4,0,99};
    Storage input = {77};
    Storage output;
    
    bool t = test( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 77);

    return t && d;
}

bool intcode_consumes_the_input()
{        
    Storage v = {3,3,99,0};
    Storage r = {3,3,99,77};
    Storage input = {77};
    Storage output;
    
    bool t = test( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 0);

    return t && d;
}

bool intcode_outputs_an_indirect_value()
{        
    Storage v = {4,3,99,77};
    Storage r = v;
    Storage input;
    Storage output;
    
    bool t = test( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 77);

    return t && d;
}

bool intcode_outputs_a_direct_value()
{        
    Storage v = {1 * 100 + 4,2,99};
    Storage r = v;
    Storage input;
    Storage output;
    
    bool t = test( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 2);

    return t && d;
}

bool add_two_direct_values()
{
    std::vector<int> v = {1101,2,3,0,99};
    std::vector<int> r = {5,2,3,0,99};
    return test( v, r );
}

bool mul_two_direct_values()
{
    std::vector<int> v = {1102,3,7,0,99};
    std::vector<int> r = {21,3,7,0,99};
    return test( v, r );
}

bool int_code_unit_test()
{
    // 1,0,0,0,99 becomes 2,0,0,0,99 (1 + 1 = 2).
    // 2,3,0,3,99 becomes 2,3,0,6,99 (3 * 2 = 6).
    // 2,4,4,5,99,0 becomes 2,4,4,5,99,9801 (99 * 99 = 9801).
    //1,1,1,4,99,5,6,0,99 becomes 30,1,1,4,2,5,6,0,99.


    // {
    //     std::vector<int> v = {1,9,10,3,2,3,11,0,99,30,40,50};
    //     std::vector<int> r = {3500,9,10,70,2,3,11,0,99,30,40,50};
    //     if (!test( v, r ))
    //     {
    //         std::cerr << " Fail 1 " << std::endl 
    //                   << "Expected: " << r << std::endl 
    //                   << "  Actual: " << v << std::endl;
    //         return false;
    //     }
    // }
    // {
    //     std::vector<int> v = {1,0,0,0,99};
    //     std::vector<int> r = {2,0,0,0,99};
    //     if (!test( v, r ))
    //     {
    //         std::cerr << " Fail 2 " << std::endl 
    //                   << "Expected: " << r << std::endl 
    //                   << "  Actual: " << v << std::endl;
    //         return false;
    //     }
    // }
    // {
    //     std::vector<int> v = {2,3,0,3,99};
    //     std::vector<int> r = {2,3,0,6,99};
    //     if (!test( v, r ))
    //     {
    //         std::cerr << " Fail 3 " << std::endl 
    //                   << "Expected: " << r << std::endl 
    //                   << "  Actual: " << v << std::endl;
    //         return false;
    //     }
    // }
    // {
    //     std::vector<int> v = {2,4,4,5,99,0};
    //     std::vector<int> r = {2,4,4,5,99,9801};
    //     if (!test( v, r ))
    //     {
    //         std::cerr << " Fail 4 " << std::endl 
    //                   << "Expected: " << r << std::endl 
    //                   << "  Actual: " << v << std::endl;
    //         return false;
    //     }
    // }
    // {
    //     std::vector<int> v = {1,1,1,4,99,5,6,0,99};
    //     std::vector<int> r = {30,1,1,4,2,5,6,0,99};
    //     if (!test( v, r ))
    //     {
    //         std::cerr << " Fail 5 " << std::endl 
    //                   << "Expected: " << r << std::endl 
    //                   << "  Actual: " << v << std::endl;
    //         return false;
    //     }
    // }


    test_runner::Tests tests = {
        {"intcode_outputs_the_input",      intcode_outputs_the_input}
        ,{"intcode_consumes_the_input",              intcode_consumes_the_input}
        ,{"intcode_outputs_an_indirect_value",              intcode_outputs_an_indirect_value}
        ,{"intcode_outputs_a_direct_value", intcode_outputs_a_direct_value}
        ,{"add_two_direct_values", add_two_direct_values}
        ,{"mul_two_direct_values", mul_two_direct_values}
    };

    return test_runner::run_tests(tests);

}
